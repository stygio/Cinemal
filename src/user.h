#ifndef USER
#define USER

#include "classes.h"

void createUser();
bool userLogin();
void userPanel(user& client);
void makeRsv(user& client);
void checkRsv(user& client);
void accWallet(user& client);

#endif // USER
