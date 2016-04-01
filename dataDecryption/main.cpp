//
//  本科毕业设计
//  main.cpp
//  dataHiding
//
//  Created by 黄路衔 on 16/3/3.
//  Copyright © 2016年 黄路衔. All rights reserved.
//

#include <iostream>
#include "commonFun.h"
#include "JpegDecompress.h"
#include "JpegDecrypt.h"

int main(int argc, const char * argv[]) {
    string embed;
    string image_decrypt;
    string image_recover;
    
    /*decrypt Jpeg bitstream*/
    embed = "/Users/huangluxian/Desktop/lena_embed.jpeg";
    image_decrypt = "/Users/huangluxian/Desktop/lena_decrypted.jpeg";
    cout << "Begin to decrypt image..." << endl;
    Jpeg_Decrypt dejpeg;
    dejpeg.read_Jpeg(embed.c_str());
    dejpeg.part_Decode();
    dejpeg.decrypt_Appended_Bit();
    dejpeg.decrypt_Qtable();
    dejpeg.write_Jpeg(image_decrypt.c_str());
    cout << "done!" << endl << endl;
    
    /*decompress jpeg*/
    image_recover = "/Users/huangluxian/Desktop/lena_decrypted.bmp";
    cout << "Begin to decompress image..." << endl;
    Jpeg_Decompress djpeg;
    djpeg.read_Jpeg(image_decrypt.c_str());
    if (false == djpeg.alloc_Mem()) {
        cout << "alloc memory fail!" << endl;
        return -1;
    }
    djpeg.start_Decode();
    djpeg.start_Decompress();
    djpeg.tran_Colorspace();
    if (false == djpeg.write_Bmp(image_recover.c_str())) {
        cout << "Write bmp fail!" << endl;
        return -1;
    }
    cout << "done!" << endl;
    return 0;
}
