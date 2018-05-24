# greenhouse
Application for a greenhouse controlled by a Raspberry Pi

## Build:
make all

## Insert to crontab:
* crontab -e
* add "*/10 * * * *  /home/pi/backup.sh" at end
* reboot to activate

## List crontab:
crontab -l
