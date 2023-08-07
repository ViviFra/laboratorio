“Telemetria drone”

Il progetto in questione si è prefissato l’obiettivo di mettere in comunicazione un drone e un pc a distanza e permettere uno scambio 
di dati fra loro, nello specifico i dati provengono da un IMU che misura angoli e velocità angolari dei quattro motori montati sul 
drone e verranno inoltre inviati i duty cycle dei motori stessi.

Al livello hardware utilizziamo a bordo del drone una scheda STM collegata al modulo wifi ESP32, ci serviamo poi di un PC per inviare
comandi e ricevere e processare dati. La scheda STM è programmata in linguaggio C con l’ausilio dell’ide STM32CUBEIDE, l’ESP32 è 
programmato attraverso ARDUINOIDE mentre sul pc utilizziamo MATLAB. Lasciamo qui sotto i link utili a scaricare i programmi in oggetto
e per quanto riguarda l’ide di Arduino la procedura per collegare in maniera corretta il nostro modulo wifi che in fase di testing 
non sarà “a bordo” del drone e quindi collegato alla scheda bensì collegato al pc di modo da poter vedere anche la sua seriale. 

Links:
https://www.st.com/en/development-tools/stm32cubeide.html

https://www.st.com/en/development-tools/stm32cubeprog.html
https://www.arduino.cc/en/software
https://randomnerdtutorials.com/installing-esp32-arduino-ide-2-0/
https://it.mathworks.com/products/matlab.html

Il ciclo del funzionamento parte da Matlab dal quale ,una volta eseguito il codice, parte in automatico il comando “dSE” che fa 
iniziare l’acquisizione/invio dati che vengono inviati ogni 100 millisecondi come impostato su un timer impostato all’interno del 
codice di STM, i dati vengono inviati per un certo periodo di tempo che possiamo liberamente impostare noi dal codice Matlab. 
Passato questo lasso di tempo in automatico Matlab invia il comando di cessazione dell’acquisizione dei dati “dND”, a questo punto 
avremo tutto lo storico dell’acquisizione salvato all’interno di una tabella e avremo anche disposizione il grafico di tutti i vari 
dati che stiamo andando ad analizzare.

Descrizione pratica/utilizzo: Si potrà procedere caricando il progetto nell’STM32CUBEIDE e poi eseguendo il tutto per caricarlo 
all’interno della scheda che da quel punto in poi, a meno di necessità di debug, potrà essere anche solo alimentata. Per il modulo 
wifi si potrà procedere caricando il codice presente nel file .ino attraverso l’ide di Arduino e anche in questo caso una volta 
caricato il codice nella scheda, a meno che non si abbia bisogno di debug/monitor seriale, essa potrà essere anche solo alimentata. 
A questo punto dovremo copiare il codice in Matlab, una volta fatto ciò ci dovremo connettere alla rete wifi “Automa”, che è generata 
dal drone, e poi eseguendo il codice da Matlab saremo in grado di completare una comunicazione completa dei dati.

Eventuali problematiche: Nel testing si sono presentante alcune problematiche ricorrenti di cui ci preme dare spiegazione o soluzione 
sin da subito. Alcune volte, soprattutto dopo un utilizzo importante la scheda una volta riattaccata tramite cavo al pc non viene più
visualizzata dall’ide come se non fosse connessa visualizzando l’errore “target not found”. In questo caso tramite STM32CubeProgrammer 
software, del quale abbiamo il link sopra, si procede a un reset della memoria della scheda che risolve immediatamente il nostro 
problema. Per quanto riguarda la ricezione dei dati alle volte ad una prima esecuzione del codice abbiamo alcuni dati “Nan” che vanno
poi a inficiare la corretta visualizzazione delle tabelle contenenti la nostra telemetria, basterà eliminare i file generati da Matlab 
in questa prima esecuzione e rieseguire il codice per ottenere dati corretti senza valori nulli.

Eventuali migliorie potrebbero essere l’integrazione con sensori propriamente funzionanti in quanto al momento di dati sono generati 
randomicamente o via Timer. Inoltre nei nostri interrupt per ottimizzare l’utilizzo della CPU abbiamo provato a utilizzare la modalità 
DMA ma abbiamo riscontrato alcune problematiche. Lasciamo il riferimento al forum ufficiale di STM per approfondire quest’ultimo 
argomento. 

https://community.st.com/t5/stm32-mcus/dma-is-not-working-on-stm32h7-devices/ta-p/49498
