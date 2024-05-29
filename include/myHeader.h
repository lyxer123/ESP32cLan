// extern "C" void sendContent(char *it);                 //expected identifier or '(' before string constant错误
// extern void sendContent(char *it);                     //with 'C' linkage 错误

extern void sendContent(char *it);
extern void send(char *it);
extern void sendc(char it);
extern void sendln(char *it);
extern char fileExists(char *fileName);