t22: t22.c
	gcc t22.c -w -lSDL2 -o t22 && gnome-terminal -e "bash -c \"./t22; echo; tput setaf 2; echo Press ENTER to repeat or CTRL+ALT+C to exit; tput sgr 0; read line; for ((NUM=1; NUM<1000; NUM++)); do ./t22;	echo; tput setaf 2; echo Press ENTER to repeat or CTRL+ALT+C to exit; tput sgr 0; read line; done; exec bash\""
clean:
	rm t22
