package com.antell.cloudhands.api.packet;

import com.antell.cloudhands.api.utils.Base16;
import com.antell.cloudhands.api.utils.TextUtils;

import java.io.DataInput;
import java.io.IOException;

/**
 * Created by dell on 2018/6/9.
 */
public class ByteData {

    private long dataSize;
    private byte[] data;

    public ByteData(DataInput in) throws IOException {

        dataSize = in.readLong();

        this.data = new byte[(int)dataSize];

        in.readFully(data,0,(int)dataSize);

    }

    public String toString(){

        StringBuffer sb = new StringBuffer();
        TextUtils.addLong(sb,"dataSize",dataSize);
        TextUtils.addText(sb,"data", Base16.toString(data));

        return sb.toString();
    }

    public long getDataSize() {
        return dataSize;
    }

    public byte[] getData() {
        return data;
    }

}
