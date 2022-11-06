

String date(int time){
	time = time/50;

	const int daySeconds =86400;  
	const int hourSeconds = 3600;
	const int minuteSeconds = 60;
	int seconds;
	int hours;
	int minutes;
	int days;
	String string;
	
	days = time / daySeconds;
	time  = time % daySeconds;
	hours = time / hourSeconds;
	time = time / hourSeconds;
	minutes = time / minuteSeconds;
	time = time / minuteSeconds;
	seconds = time;
	
	string = ("days " +String(days) + "hours "+String(hours) + "minutes "+ String(minutes) + "seconds " + String(seconds));
	return string;


}
