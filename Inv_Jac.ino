void Inv_Jac() {
  //inverse jacobian equations
  Lv1 = -((((x + a) / (z + L1)) * Xv) + (((y + b) / (z + L1)) * Yv) + Zv);

  Lv2 = -((((x - a) / (z + L2)) * Xv) + (((y + b) / (z + L2)) * Yv) + Zv);

  Lv3 = -(((x / (z + L3)) * Xv) + (((y + c) / (z + L3)) * Yv) + Zv);
  //---------------------------------------------------------------------------------
  
  //Coversion to steps/second 
  speeda = (Lv1 / (11.25 * 2 * pi)) * DS  ;
  speedb = (Lv2 / (11.25 * 2 * pi)) * DS  ;
  speedc = (Lv3 / (11.25 * 2 * pi)) * DS  ;


}
