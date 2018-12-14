#include <iostream>
using namespace std;

long calculateDays(long date1, long date2) {
  // ensure that date1 is before date2
  if (date1 > date2) {
    long temp = date1;
    date1 = date2;
    date2 = temp;
  }

  long res = 0;
  long date[2];
  date[0] = date1;
  date[1] = date2;

  // extract year, month, day from each date and store into arrays
  int yr[2];
  int m[2];
  int d[2];
  for (int i = 0; i < 2; i++) {
    yr[i] = date[i] / 10000;
    m[i] = (date[i] / 100) % 100;
    d[i] = date[i] % 100;
  }

  bool lpyr1 = false;
  if ((yr[0] % 4 == 0) && (yr[0] % 100 != 0) || (yr[0] % 400 == 0)) {
    lpyr1 = true;
  }

  // calculate days til end of first month of first date
  int dDays1 = 0;
  // if yr and month are the same
  if (yr[0] == yr[1] && m[0] == m[1]) {
    dDays1 = d[1] - d[0];
  }
  else if (((m[0] % 2 == 1) && (m[0] < 8)) || ((m[0] % 2 == 0) && (m[0] >= 8))) {
    dDays1 = 31 - d[0];
  }
  else if ((m[0] == 4) || (m[0] == 6) || (m[0] == 9) || (m[0] == 11)) {
    dDays1 = 30 - d[0];
  }
  else if (lpyr1) {
    dDays1 = 29 - d[0];
  }
  else {
    dDays1 = 28 - d[0];
  }

  // calculate days for remaining months of the first year
  int mDays1 = 0;
  // while the current month number is < 13 AND
  // it can't be > month of the second date when the years are the same 
  for (int i = m[0] + 1; ((i < 13) && (yr[0] != yr[1])) || (i < m[1]); i++) {
    // cout << "i is " << i << endl;

    // if the month is 1,3,5,7 (odd numbers less than 8)
    // or 8,10,12 (even numbers >= 8)
    if (((i % 2 == 1) && (i < 8)) || ((i % 2 == 0) && (i >= 8))) {
      mDays1 += 31;
      // cout << "adding 31" << endl;
    }
    else if ((i == 4) || (i == 6) || (i == 9) || (i == 11)) {
      mDays1 += 30;
      // cout << "adding 30" << endl;
    }
    else if (lpyr1) {
      mDays1 += 29;
      // cout << "adding 29" << endl;
    }
    else {
      mDays1 += 28;
      // cout << "adding 28" << endl;
    }
  }

  // calculate days for each of the subsequent years except the last
  long yDays = 0;
  for (int i = yr[0] + 1; i < yr[1]; i++) {
    if ((i % 4 == 0) && (i % 100 != 0) || (i % 400 == 0)) {
      yDays += 366;
    }
    else {
      yDays += 365;
    }
  }

  // calculate days of months of last year until the last month
  int mDays2 = 0;
  // while the current month is less than the month of the second date AND
  // the years are different
  for (int i = 1; (i < m[1]) && (yr[0] != yr[1]); i++) {
    if (((i % 2 == 1) && (i < 8)) || ((i % 2 == 0) && (i >= 8))) {
      mDays2 += 31;
    }
    else if ((i == 4) || (i == 6) || (i == 9) || (i == 11)) {
      mDays2 += 30;
    }
    else if (lpyr1) {
      mDays2 += 29;
    }
    else {
      mDays2 += 28;
    }
  }

  // calculate the days in that last month
  int dDays2 = 0;
  // if either yr or month are different
  if (yr[0] != yr[1] || m[0] != m[1]) {
    dDays2 = d[1];
  }

  // cout << "dDays1 = " << dDays1 << endl;
  // cout << "mDays1 = " << mDays1 << endl;
  // cout << "yDays = "  << yDays  << endl;
  // cout << "mDays2 = " << mDays2 << endl;
  // cout << "dDays2 = " << dDays2 << endl;

  res = dDays1 + mDays1 + yDays + mDays2 + dDays2;
  
  return res;
}

int main()
{
  cout << "please input two dates (space or enter between) yyyymmdd" << endl;
  long date1;
  long date2;
  cin >> date1 >> date2;

  cout << calculateDays(date1, date2) << endl;
}
