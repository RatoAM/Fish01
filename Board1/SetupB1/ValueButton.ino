void ValueButton(){
  F = Firebase.getInt("device/control/Food");
  H = Firebase.getInt("device/control/heater");
  WtIn = Firebase.getInt("device/control/Pump");
  WtOut = Firebase.getInt("device/control/PumpOUT");
  WtH = Firebase.getInt("device/control/PumpWait");
  if(F == 1){
    NexText.setComponentValue("bt0", 1);
    }else{
    NexText.setComponentValue("bt0", 0);
    }
  if(H == 1){
    NexText.setComponentValue("bt1", 1);
    }else{
    NexText.setComponentValue("bt1", 0);
    }
  if(WtIn == 1){
    NexText.setComponentValue("bt2", 1);
    }else{
    NexText.setComponentValue("bt2", 0);
    }
  if(WtOut == 1){
    NexText.setComponentValue("bt3", 1);
    }else{
    NexText.setComponentValue("bt3", 0);
    }
  if(WtH == 1){
    NexText.setComponentValue("bt4", 1);
    }else{
    NexText.setComponentValue("bt4", 0);
    }
  }
