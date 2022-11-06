	
	const int daySeconds =86399;  
	const int hourSeconds = 3599;
	const int minuteSeconds = 59;
	int seconds;
	int hours;
	int minutes;
	int days;
	String string;

int getTime(int time){
	return time/50;
}



String date(int time)
{
	time = getTime(time);

	
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

int hrs(int time){
	time = getTime(time);

	
	days = time / daySeconds;
	time  = time % daySeconds;
	hours = time / hourSeconds;
	time = time / hourSeconds;
	minutes = time / minuteSeconds;
	time = time / minuteSeconds;
	seconds = time;
	return hrs;
}

int runCycles(int time,int timer,int sec, int pin){
  int newTime = getTime(time);
  if(newTime >= timer){
    digitalWrite(pin, HIGH);
    delay(sec);
    digitalWrite(pin, LOW);
    return 0;
  }
  else{
    return  time;
  }
}
