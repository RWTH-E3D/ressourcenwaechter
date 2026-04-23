// ==== Predict user comfort ====

void predicted_comfort(){  
  // predict comfort and update level system while using device
  // No actions during sleep
  if (status_updated && isSleep == false) {
    // calculate IEQI
    IEQI();
    
    // Update level system
    level_system();
    
    status_updated = false;
  }
}

// symmetric index, e.g. worst - bad - good - very good - good - bad - worst
float calc_index_sym(float val, float min_iii, float min_ii, float min_i, float max_i, float max_ii, float max_iii) {
  float mean;
  float index_unit;
  float index;
  if(val < max_i && val >= min_i){
    mean = (max_i + min_i) / 2;
    index_unit = (3.0 - 2.7) * 2 / (max_i - min_i);
    index = 3.0 - (abs(val - mean) * index_unit);
  }  
  else if(val < max_ii && val >= min_ii){
    if(val < min_i){
      index_unit = (2.7 - 2.0) / (min_i - min_ii);
      index = 2.7 - (abs(val - min_i) * index_unit);
    }
    else if(val >= max_i){
      index_unit = (2.7 - 2.0) / (max_ii - max_i);
      index = 2.7 - (abs(val - max_i) * index_unit);
    }
  }
  else if(val < max_iii && val >= min_iii){
    if(val < min_ii){
      index_unit = (2.0 - 1.0) / (min_ii - min_iii);
      index = 2.0 - (abs(val - min_ii) * index_unit);
    }
    else if(val >= max_ii){
      index_unit = (2.0 - 1.0) / (max_iii - max_ii);
      index = 2.0 - (abs(val - max_ii) * index_unit);
    }
  }
  else{
    index = 0;  
  }
  return index;
}

// asymmetric index, e.g. very good - good - bad - worst
float calc_index_asym(float val, float max_i, float max_ii, float max_iii) {
  float min_val=0;
  float mean;
  float index_unit;
  float index;
  if(val < max_i){
    index_unit = (3.0 - 2.7) / (max_i - min_val);
    index = 3.0 - (abs(val - min_val) * index_unit);
  }  
  else if(val < max_ii){
    index_unit = (2.7 - 2.0) / (max_ii - max_i);
    index = 2.7 - (abs(val - max_i) * index_unit);
  }
  else if(val < max_iii){
    index_unit = (2.0 - 1.0) / (max_iii - max_ii);
    index = 2.0 - (abs(val - max_ii) * index_unit);
  }
  else{
    index = 0.0;  
  }
  return index;
}

// asymmetric index reversed, e.g. worst - bad - good - very good
float calc_index_asym_rev(float val, float max_i, float max_ii, float max_iii) {
  float mean;
  float index_unit;
  float index;
  if(val < max_i){
    index = 0;
  }  
  else if(val < max_ii){
    index_unit = (2.0 - 1.0) / (max_ii - max_i);
    index = 2.0 - (abs(val - max_i) * index_unit);
  }
  else if(val < max_iii){
    index_unit = (2.7 - 2.0) / (max_iii - max_ii);
    index = 2.7 - (abs(val - max_ii) * index_unit);
  }
  else{
    index = 3.0;  
  }
  return index;
}

float v_relative(float v_val, float met_val){
  float vr;
  if(met_val > 1){
    vr = v_val + 0.3 * (met_val - 1);
  }
  else{
    vr = v_val;
  }
  return vr;
}



float pmv_iso(float tdb, float tr, float vr, float rh, float met, float clo, float wme = 0){
  float pa = rh * 10 * exp(16.6536 - 4030.183 / (tdb + 235));

  float icl = 0.155 * clo;
  float m = met * 58.15;
  float w = wme * 58.15;
  float mw = m - w;
  float f_cl;
  if (icl <= 0.078){
    f_cl = 1 + (1.29 * icl);
  }
  else{
    f_cl = 1.05 + (0.645 * icl);
  }

  float hcf = 12.1 * sqrt(vr);
  float hc = hcf;
  float taa = tdb + 273;
  float tra = tr + 273;
  float t_cla = taa + (35.5 - tdb) / (3.5 * icl + 0.1);

  float p1 = icl * f_cl;
  float p2 = p1 * 3.96;
  float p3 = p1 * 100;
  float p4 = p1 * taa;
  float p5 = (308.7 - 0.028 * mw) + (p2 * pow((tra / 100.0),4));
  float xn = t_cla / 100;
  float xf = t_cla / 50;
  float eps = 0.00015;

  int n = 0;
  while (abs(xn - xf) > eps){
      xf = (xf + xn) / 2;
      float hcn = 2.38 * pow(abs(100.0 * xf - taa),0.25);
      if (hcf > hcn){
        hc = hcf;
      }
      else{
        hc = hcn;
      }
      xn = (p5 + p4 * hc - p2 * pow(xf,4)) / (100 + p3 * hc);
      n += 1;
      if (n > 150){
        break;  
      }
  }
  float tcl = 100 * xn - 273;

  float hl1 = 3.05 * 0.001 * (5733 - (6.99 * mw) - pa);
  float hl2;
  if (mw > 58.15){
    hl2 = 0.42 * (mw - 58.15);
  }
  else{
    hl2 = 0;
  }
  float hl3 = 1.7 * 0.00001 * m * (5867 - pa);
  float hl4 = 0.0014 * m * (34 - tdb);
  float hl5 = 3.96 * f_cl * (pow(xn,4) - pow((tra / 100.0),4));
  float hl6 = f_cl * hc * (tcl - tdb);

  float ts = 0.303 * exp(-0.036 * m) + 0.028;
  float pmv = ts * (mw - hl1 - hl2 - hl3 - hl4 - hl5 - hl6);

  if (pmv < -3){
    pmv = -3;
  }
  else if (pmv > 3){
    pmv = 3;
  }
  return pmv;
}

void TCI(){
  float v_rel = 0;
  if (WindSensorisAvailable) {
    v_rel = v_relative(windSpeed, 1.2);
  }
  if (RadTempSensorisAvailable) {
    TCI_val = 3.0 - abs(pmv_iso(temperature, radTemperature, v_rel, humidity, met, clo));
  } else {
    TCI_val = 3.0 - abs(pmv_iso(temperature, temperature, v_rel, humidity, met, clo));
  }
}

void SCI(){
  SCI_val = calc_index_asym(sound,sound_most_comfort_max,sound_comfort_max,sound_not_comfort_max);
}

void LCI(){
  LCI_val = calc_index_asym_rev(light,light_not_comfort_min,light_comfort_min,light_most_comfort_min);
}

void PCI(){
  PCI_val = calc_index_sym(pressure,pressure_not_comfort_min,pressure_comfort_min,pressure_most_comfort_min,pressure_most_comfort_max,pressure_comfort_max,pressure_not_comfort_max);
}

void IAQI(){
  float IAQI_val_voc = 0;
  float IAQI_val_co2 = 0;
  if (SGP40isAvailable) {
    IAQI_val_voc = calc_index_asym(vocIndex,voc_good_max,voc_moderate_max,voc_unhealthy_max);
  }
  if (SCD30isAvailable) {
    IAQI_val_co2 = calc_index_asym(co2,co2_good_max,co2_moderate_max,co2_unhealthy_max);
  }
  IAQI_val = (IAQI_val_voc + IAQI_val_co2 ) / (int(SGP40isAvailable) + int(SCD30isAvailable));
}

void IEQI(){
  // worst 0 - 1 - 2 - 2.7 - 3.0 best
  if (BME280isAvailable) {
    TCI();
  } else {
    TCI_val = 0;
  }
  if (SoundSensorisAvailable) {
    SCI();
  } else {
    SCI_val = 0;
  }
  if (VEML7700isAvailable) {
    LCI();
  } else {
    LCI_val = 0;
  }
  if (BME280isAvailable) {
    PCI();
  } else {
    PCI_val = 0;
  }
  if (SCD30isAvailable || SGP40isAvailable) {
    IAQI();
  } else {
    IAQI_val = 0;
  }
  // worst 0 - 33 - 66 - 90 - 100 best
  IEQI_val = (TCI_weight * TCI_val + SCI_weight * SCI_val + LCI_weight * LCI_val + PCI_weight * PCI_val + IAQI_weight * IAQI_val) * 100 / 
             (
                3 * (
                  (TCI_weight + PCI_weight) * int(BME280isAvailable) + SCI_weight * int(SoundSensorisAvailable) + LCI_weight * int(VEML7700isAvailable) + IAQI_weight * int(SCD30isAvailable)
                )
             );
}
