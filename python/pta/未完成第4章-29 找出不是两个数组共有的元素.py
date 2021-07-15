ss1=input().split(' ')
ss2=input().split(' ')
s1=''
s2=''
for i in range(len(ss1)):
    s1+=int(ss1[i])
for i in range(len(ss2)):
    s2+=int(ss2[i])
same=''
for i in range(len(s1)):
    if s2.find(s1[i]) and same.find(s1[i])==0:
        same+=(s1[i])
for i in range(len(s2)):
    if s1.find(s2[i]) and same.find(s2[i])==0:
        same+=(s2[i])
print(same)
