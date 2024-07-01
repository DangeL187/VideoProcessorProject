import VideoProcessorProject

from datetime import datetime
import io
from PIL import Image, ImageTk
import threading
import tkinter as tk


class Player:
    def __init__(self, video_file_path):
        self.root = tk.Tk()
        self.root.title("Player")
        self.root.protocol("WM_DELETE_WINDOW", self.onClose)
        self.video = VideoProcessorProject.VideoProcessor(video_file_path)

        self.is_running = True
        self.image = None
        self.label = tk.Label(self.root)
        self.label.pack()

        self.timers = []

        thread = threading.Thread(target=self.run)
        thread.start()
        self.update_image()
        self.root.mainloop()

    def onClose(self):
        self.is_running = False
        self.root.destroy()
        self.video.stop()

    def run(self):  # main method
        while self.is_running:
            start = datetime.now()  # start timer

            frame = self.video.getFrame()  # get current frame
            if len(frame.data()) == 0:  # ignore empty frames
                continue

            # Change current image:
            img = Image.open(io.BytesIO(frame.data()))
            self.image = ImageTk.PhotoImage(image=img)

            self.timers.append((datetime.now() - start).microseconds / 1000000)  # stop timer

            if len(self.timers) % 100 == 0 and len(self.timers) > 0:  # each 100th frame, example: 25fps video will print this message once in 4 seconds
                print(frame.width(), 'x', frame.height(), 'Time:', frame.timestamp())
                print('FRAME LOADING AVG:', sum(self.timers) / len(self.timers))

    def update_image(self):
        if self.image is not None:
            self.label.imgtk = self.image
            self.label.config(image=self.image)
        self.root.after(1, self.update_image)


if __name__ == '__main__':
    slideshow = Player('caban.mp4')
