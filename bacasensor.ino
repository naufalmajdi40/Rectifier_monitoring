void bacaSensor(){  
dataSensor="";
dataSensor+="@BMS*";
dataSensor+="0001";
dataSensor+="*";
dataSensor+=String(teg1);
dataSensor+="*";
dataSensor+=String(teg2);
dataSensor+="*";
dataSensor+=String(teg3);
dataSensor+="*";
dataSensor+=String(arus1);
dataSensor+="*";
dataSensor+=String(arus2);
dataSensor+="*";
dataSensor+=String(arus3);
dataSensor+="*";
dataSensor+=String(temp1);
dataSensor+="*";
dataSensor+=String(temp2);
dataSensor+="*";
dataSensor+=String(hum1);
dataSensor+="*";
dataSensor+=String(hum2);
dataSensor+="*";

}
