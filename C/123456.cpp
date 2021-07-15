function res = RGB888toRGB444(imgdata, filename)
cnt = 3;
[h,l,c] = size(imgdata);
res(1:h,1:l,1:c)=0;
file = fopen(filename,"w");
fprintf(file,"MEMORY_INITIALIZATION_RADIX=16;\nMEMORY_INITIALIZATION_VECTOR=\n");
res(1,1,1) = floor((imgdata(1,1,1)+1) / 16);
if(res(1,1,1)==16)res(1,1,1) = res(1,1,1)-1;end
res(1,1,2) = floor((imgdata(1,1,2)+1) / 16);
if(res(1,1,2)==16)res(1,1,2) = res(1,1,2)-1;end
res(1,1,3) = floor((imgdata(1,1,3)+1) / 16);
if(res(1,1,3)==16)res(1,1,3) = res(1,1,3)-1;end
fprintf(file,"%c%c%c",dec2hex(res(1,1,1),1),dec2hex(res(1,1,2),1),dec2hex(res(1,1,3),
1));
for i = 1: h
for j = 1 : l
if(i~=1 || j~= 1)
for k = 1 : c
res(i,j,k) = floor((imgdata(i,j,k)+1) / 16);
if(res(i,j,k)==16)res(i,j,k) = res(i,j,k)-1;end
cnt = cnt + 1;
end
fprintf(file,",\n%c%c%c",dec2hex(res(i,j,1),1),dec2hex(res(i,j,2),1),dec2hex(res(i,j,
3),1));
end
end
end
imshow(res);
% for i = 1 : h
% for j = 2 : l
% fprintf(file,",\n%c%c%c",resH(i,j,1),resH(i,j,2),resH(i,j,3));
% end
% end
fprintf(file,";\n");
fprintf(file,"%d",cnt);
fclose(file);