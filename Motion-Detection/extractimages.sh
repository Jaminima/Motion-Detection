cd ./Images
ffmpeg -i video.mp4 -filter:v fps=fps=600/60 %0d.png