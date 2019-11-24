

/*  delay impl  */
void delay(int ms) {
	long pause;
	clock_t now, then;
	
	pause = ms*(CLOCKS_PER_SEC/1000);
	now = then = clock();
	while( (now-then) < pause ) {
		now = clock();
	}
}
