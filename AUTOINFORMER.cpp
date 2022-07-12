main(){
        const bufSize = 96
        new size = 20
        new iBuf{bufSize}
        new oBuf{24}
        new j = 0
        ExecCommand("AUTOINFORMER")
        GetBinaryDataFromCommand(iBuf, bufSize)
        for(new i = 0; i < 64; i++){
            if(iBuf{i} == 0x52 && iBuf{i+1} == 0x6F && iBuf{i+2} == 0x75 && iBuf{i+3} == 0x74 && iBuf{i+4} == 0x3D)
            {
                for(new j = 0; j < 24; j++){
                    if(iBuf{j + i + 5} != 0x2C){
                        oBuf{j} = iBuf{j + i + 5}
                    }
                    else{
                        break
                    }
                }
            }
        }
        Diagnostics("%s", oBuf)
        TagWriteArray(0x6A,size,oBuf)
    }
