%WiFi communication
%open communication
t = tcpclient("192.168.4.1", 80);

%comandi:
% "dSE" comando per acquisire dati dal drone
% "dND" comando per interrompere l'acquisizione

command="dSE";
writeline(t, command); %invia il comando
%t.Timeout=30;
flush(t)
configureTerminator(t, "LF");
configureCallback(t, "terminator", @readASCIIFcn);
tempo_acquisizione = 120; %tempo di acquisizione in secondi
pause(tempo_acquisizione); %pausa
command="dND";
writeline(t, command); %invia il comando
if(command=="dND")
    
    %data_matrix = readmatrix('telemetria_drone.txt', 'FileType', 'text')
    data_matrix = readmatrix('telemetria_drone.txt');

    roll=data_matrix(:,1);
    pitch=data_matrix(:,2);
    yaw=data_matrix(:,3);
    Vr=data_matrix(:,4);
    Vp=data_matrix(:,5);
    Vy=data_matrix(:,6);
    mot1=data_matrix(:,7);
    mot2=data_matrix(:,8);
    mot3=data_matrix(:,9);
    mot4=data_matrix(:,10);
 
    % plot dei dati
    figure;
 
    % plot per roll, pitch e yaw
    subplot(3, 1, 1);
    plot(roll);
    hold on;
    plot(pitch);
    plot(yaw);
    legend('Roll', 'Pitch', 'Yaw');
    xlabel('Sample');
    ylabel('Angle (degrees)');
    title('Orientation Angles');

    % plot per Vr, Vp, Vy
    subplot(3, 1, 2);
    plot(Vr);
    hold on;
    plot(Vp);
    plot(Vy);
    legend('Vr', 'Vp', 'Vy');
    xlabel('Sample');
    ylabel('Angular Velocity');
    title('Angular Velocities');

    % plot per mot1, mot2, mot3, mot4
    subplot(3, 1, 3);
    plot(mot1);
    hold on;
    plot(mot2);
    plot(mot3);
    plot(mot4);
    legend('Mot1', 'Mot2', 'Mot3', 'Mot4');
    xlabel('Sample');
    ylabel('Duty Cycle');
    title('Motor Duty Cycle');

  %  delete telemetria_drone.txt;

end
 pause(1);
 delete telemetria_drone.txt;

%%%%%%% funzione callback per la lettura e il salvataggio dei dati %%%%%%%

function readASCIIFcn(t, ~)

    t.UserData=readline(t); %leggi i dati dal drone

    %salva i dati in un file
    writematrix(t.UserData,'file.txt','WriteMode','append');

    % imposta il nome del file da leggere
    nome_file = 'file.txt';

    % leggi i dati dal file
    dati = fileread(nome_file);

    roll = str2double(dati(1:3)) + str2double(dati(4)) / 10;
    pitch = str2double(dati(5:7)) + str2double(dati(8)) / 10;
    yaw = str2double(dati(9:11)) + str2double(dati(12)) / 10;

    Vr = str2double(dati(13:16)) / 100;
    Vp = str2double(dati(17:20)) / 100;
    Vy = str2double(dati(21:24)) / 100;
 
    mot1 = str2double(dati(25:26)) / 10;
    mot2 = str2double(dati(27:28)) / 10;
    mot3 = str2double(dati(29:30)) / 10;
    mot4 = str2double(dati(31:32)) / 10;

    % crea una tabella per i dati con i nomi delle colonne desiderati
    tabella_dati = table(roll, pitch, yaw, Vr, Vp, Vy, mot1, mot2, mot3, mot4);

    disp (tabella_dati);

    writetable(tabella_dati, 'telemetria_drone.txt', 'Delimiter', '\t', 'WriteMode', 'Append');

    delete file.txt;    

end