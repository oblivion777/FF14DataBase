
import os

outFileList=open("D:/FF14DataBase/_log/fileList-utf8.txt","wb+")
path="F:\\[FFXIV]MODS\\MOD"
for root,dirs,files in os.walk(path): 
    for file in files: 
        #print(os.path.join(root,file))
        buff=(os.path.join(root,file)).encode("utf-8")
        outFileList.write(buff)
        outFileList.write("\n".encode("utf-8"))
print("Created [D:/FF14DataBase/_log/fileList-utf8.txt] successfully")