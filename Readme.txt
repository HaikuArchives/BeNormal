BeNormal is a small command line program designed to normalise 
wav files. To the non audio buff, that means it makes an attempt to
make all wav files the same volume at their loudest point.
Its just a small little thing that I wrote because I got bored
with constantly altering the volume in CL-Amp when listening
to the mp3's that I've made. 

I've also included a modified version of Scott Hackers ripenc that uses 
BeNormal. just copy over the script to /boot/home/config/bin/

BeNormal accepts one parameter, the input filename. The
resuting WAV file is output to stdout. 

E.g.
To normalise a wav called input.wav, and save it
as output.wav you use.

BeNormal input.wav > output.wav 

To feed it through Gogo to mp3 it you would use

BeNormal input.wav | gogo stdin output.wav 

You may be wondering what the bad news is, well
this version takes a lot of memory as it reads the
whole wav into memory, and it takes time. Here are
some not very scientific facts and figures. Note that converting
a BeNoramlised wav from harddrive to a mp3 file is actually faster that
the straight conversion.

example wav: Black Planet by the Sisters of Mercy
size: 47.41 MB
playing time: 4:42
time to rip: 0:35
PC specs


Time to Normalise from Hard drive: 0:27
Time to Normalise from Hard drive redirecting output to /dev/null : 0:18

CD to mp3 timings.
results are total time taken, mp3 conversion factor, encoding time

CD -> BeNormal -> Gogo
2:31.06  2.68x  105.064  

CD->Gogo
2.21.28 1.99x  141.276  rip from CD

Harddrive-> BeNormal -> Gogo
1.45.64  2.67x  105.640  

Harddrive -> Gogo
1.52.87 2.50x  112.871


