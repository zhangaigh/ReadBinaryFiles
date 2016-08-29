

#include <stdio.h>
#include <iostream>
#include "boost/filesystem.hpp"
#include <boost/foreach.hpp>
#include <cv.h>
#include <highgui.h>
#include <opencv2/imgproc/imgproc.hpp>

#define WIDTH 640
#define HEIGHT 480

using namespace std;
using namespace boost::filesystem;


/** Read binary files in a directory and extract Y component of YUV format
*  
*/
void readDir(const std::string& dir_, vector<string>& files_vec, vector<string>& file_names)
{
    files_vec.clear();
    boost::filesystem::path targetDir(dir_);
    boost::filesystem::recursive_directory_iterator iter(targetDir), eod;
    BOOST_FOREACH(boost::filesystem::path const& i, make_pair(iter, eod))
    {
        if (is_regular_file(i))
        {
            cout << i.string() << endl;
            files_vec.push_back(i.string());
            file_names.push_back(i.stem().string());
        }
    }
}
int main(int argc, char **argv)
{
    FILE *stream;
    int img_size = WIDTH * HEIGHT;

    if(argc != 2)
    {
        cerr << endl << "Usage: ./readBinary path_to_sequence" << endl;
        return 1;
    }

    vector<string> files;
     vector<string> files_name;
    readDir(string(argv[1]), files,files_name);


    // Open files and read data
    unsigned char * buff = (unsigned char *) malloc(img_size);
    
    for (int i = 0; i < files.size(); i ++)
    {
         if( (stream = fopen( files[i].c_str(), "r" )) != NULL ) 
        {
            int numread;
            numread = fread( buff, sizeof( unsigned char ), img_size, stream );
            string base = "../img/";
            string outfile = base + files_name[i] + ".png";
            boost::filesystem::path img_dir(base);
            if (!boost::filesystem::exists(boost::filesystem::status(img_dir)))
            {
                 if(boost::filesystem::create_directory(img_dir))
                {
                    std::cout << "Success" << "\n";
                }
            }
            cv::Mat img(HEIGHT, WIDTH, CV_8UC1, buff);
            imwrite( outfile, img );
            printf( "Number of items read = %d\n", numread );
            fclose( stream );
        }
        else // adressing error
        {
            cerr <<  "File could not be opened" << endl;
        }
    }
   
}