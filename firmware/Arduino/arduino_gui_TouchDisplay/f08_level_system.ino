// ==== Level and EXP system ====

void level_system() {
  // store last level and exp info to minimize the number of writes if level and exp do not change
  previousLevel = level;
  previousExp = expNow;

  // calculate expNext
  expNext = calc_expNext(level);

  // obtain exp based on IEQI
  if (IEQI_val >= 90) {
    unsigned int expObt = round(IEQI_val / 10.0);
    expNow += expObt;
  } else if (IEQI_val >= 67) {
    unsigned int expObt = round(IEQI_val / 11.0);
    expNow += expObt;
  } else if (IEQI_val >= 33) {
    unsigned int expObt = round(IEQI_val / 20.0);
    expNow += expObt;
  }
  
  // check if level up
  if (expNow >= expNext) {
    // level up
    level++;
    // max level 999
    if (level > 999) {level = 999;}
    // calculate expNow and new expNext
    expNow = expNow - expNext;
    expNext = calc_expNext(level);
  }

  // save level & exp data if changed
  if (level != previousLevel || expNow != previousExp){
    char new_level_exp[30];
    sprintf(new_level_exp, "%d;%d;", level, expNow);
    sd_write(filename_userdata, new_level_exp);
    debug_println("SD - user data updated!");
  }
}

unsigned int calc_expNext(unsigned int lv) {
  unsigned int expNx;
  if (lv <= 20) {
    expNx = 200 + pow(lv,4);
  } 
  else if (lv <= 46) {
    expNx = 160200 + 9000 * (lv - 20);
  } 
  else {
    expNx = 400000;
  }
  return expNx;
}
