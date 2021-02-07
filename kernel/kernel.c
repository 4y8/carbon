char msg[] = "Hello world!";

int
kernel_main()
{
	*(long *)0xB8000 = 0x2f592f412f4b2f4f;
	int i = 0;
	for (char *s = (char *)msg; *s; ++s) {
		*(char *)(0xB8000 + (long)i++) = *s;
		*(unsigned char *)(0xB8000 + (long)i++) = 0b00101111;
	}
	while(1);
}
