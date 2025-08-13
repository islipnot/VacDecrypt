# Summary
This allows you to easily decrypt strings found in VAC modules. You must identify the key and decryption type (XOR or ROL), 
which can be done by xrefing the encrypted string and looking for a while loop that looks like one of the two below.

### ROL decryption
```C
v7 = Advapi32dll[0];
if ( Advapi32dll[0] )
{
  v8 = Advapi32dll;
  do
  {
    *v8++ = __ROL1__(v7, 3);
    v7 = *v8;
  }
  while ( *v8 );
}
```

### XOR decryption
```C
v42 = NtReadVirtualMemory;
v43 = 104;
do
{
  *v42++ = v43 ^ 38;
  v43 = *v42;
}
while ( *v42 );
```

# Usage
Argument format: \<string\> \<type\> \<key\> </br>
Types: r == ROL, x == XOR </br>
String should be surrounded by quotes for safety.