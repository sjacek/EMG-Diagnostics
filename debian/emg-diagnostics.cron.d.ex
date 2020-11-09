#
# Regular cron jobs for the emg-diagnostics package
#
0 4	* * *	root	[ -x /usr/bin/emg-diagnostics_maintenance ] && /usr/bin/emg-diagnostics_maintenance
