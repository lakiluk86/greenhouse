# greenhouse
Application for a greenhouse controlled by a Raspberry Pi

Build:<br>
make all

Insert to crontab:<br>
crontab -e<br>
add "*/10 * * * *  /home/pi/backup.sh"<br>
reboot then

List crontab:<br>
crontab -l
