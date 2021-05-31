void codegen();
void codegen()
{
	int a;
	a = 1;
  digitalWrite(26, 1);
  delay(a++ *1000);
  digitalWrite(26, 0);
  delay(++a*1000);
}
