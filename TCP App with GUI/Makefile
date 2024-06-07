part2:
	gcc serveurTCP.c -o serveurTCP	
	gcc clientTCPUI.c -o clientTCPUI `pkg-config --cflags --libs gtk4`
clean:
	rm -rf *.o *.gch serveurTCP
	rm -rf *.o *.gch clientTCPUI
