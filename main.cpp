/*
 MTAG (https://github.com/psemiletov/mtag)
 
 This code is Public Domain.
 
 Peter Semiletov <tea@list.ru>, http://semiletov.org
*/

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "libretta_utils.h"
#include "libretta_string_utils.h"
#include "libretta_pairfile.h"


#include <fileref.h>
#include <tstring.h>


using namespace std;
using namespace TagLib;


void write_tags (const string &rules_file, const string &ext)
{
  std::vector <string> files = files_get_list (current_path(), ext);
  std::sort (files.begin(), files.end());
  if (files.size() == 0)
    {
     cout << "No files to process! Please provide some files. Read README for the details." << endl;
     return;
    }

  string rules_file_data = string_file_load (rules_file);
  
  vector<string> vs = string_split (rules_file_data, "###");

  for (size_t i = 0; i < vs.size(); i++)
     {
      string fname = files[i];
      cout << "process:" << fname << endl;
      TagLib::FileRef f (fname.c_str());
      CPairFile pf (vs[i], true);

      /*
       Nasty hack - the first tag at the first tags block,
       by the mystical reason, cannot be parsed properly.
      There are two medicines from this STRANGE behaviour.
      1. Manually (but not programmatically from mtag)
      add the obsolete first line to the RULES file.
      2. Add the obsolete key-val to the tags structure.
      */

     pf.values["@testkey"] = "testvalue";
     for (auto & kvp : pf.values)
        {
         string key = kvp.first;
         string val = pf.values[kvp.first];
         
         cout << key << " --------------------- " << val << endl;
         
         TagLib::String ts (val, TagLib::String::Type::UTF8);
         
         if (key == "@artist")
            f.tag()->setArtist (ts);
         else
         if (key == "@title")
            f.tag()->setTitle (ts);
         else
         if (key == "@album")
            f.tag()->setAlbum (ts);
         else
         if (key == "@genre")
            f.tag()->setGenre (ts);
         else
             if (key == "@comment")
         f.tag()->setComment (ts);
         else
         if (key == "@year")
            f.tag()->setYear (stoi (val));
         else
         if (key == "@track")
            f.tag()->setTrack (stoi (val));
        }

     f.save();
     cout << "tag: saved" << endl;
    }
}


void extract_tags (const string &rules_file, const string &ext)
{
  std::vector <string> files = files_get_list (current_path(), ext);
  std::sort (files.begin(), files.end());


  if (files.size() == 0)
    {
     cout << "No files to process! Please provide some files. Read README for the details." << endl;
     return;
    }
     
  
  vector<string> vs;
  
  for (size_t i = 0; i < files.size(); i++)
     {
      string fname = files[i];
          
      cout << "process:" << fname << endl;
      
      TagLib::FileRef f (fname.c_str());
      
      TagLib::String ts;
      
      ts = f.tag()->artist();
      if (! ts.isEmpty())
        {
         string pair = "@artist";
         pair += "=";
         pair += ts.toCString(true);
         vs.push_back (pair);
        } 
   
      ts = f.tag()->title();
      if (! ts.isEmpty())
        {
         string pair = "@title";
         pair += "=";
         pair += ts.toCString(true);
         vs.push_back (pair);
        } 
   
      ts = f.tag()->album();
      if (! ts.isEmpty())
        {
         string pair = "@album";
         pair += "=";
         pair += ts.toCString(true);
         vs.push_back (pair);
        } 
   
      ts = f.tag()->comment();
      if (! ts.isEmpty())
        {
         string pair = "@comment";
         pair += "=";
         pair += ts.toCString(true);
         vs.push_back (pair);
        } 
   
   
      ts = f.tag()->genre();
      if (! ts.isEmpty())
        {
         string pair = "@genre";
         pair += "=";
         pair += ts.toCString(true);
         vs.push_back (pair);
        } 
   
      unsigned int x = 0;
   
      x = f.tag()->year();
      if (x != 0)
        {
         string pair = "@year";
         pair += "=";
         pair += std::to_string (x);
         vs.push_back (pair);
        } 
   
      x = f.tag()->track();
      if (x != 0)
        {
         string pair = "@track";
         pair += "=";
         pair += std::to_string (x);
         vs.push_back (pair);
        } 
   
   
      vs.push_back ("###");
      
      cout << "tags: extracted" << endl;
     }
     
  vs.pop_back();   
     
  ofstream outputFile (rules_file);

  if (outputFile.is_open())
    {
     for (string s: vs) 
        { 
         outputFile << s << endl; 
        }
    }   
  else 
      cout << "Unable to write output file" << endl;
}


int main (int argc, char *argv[])
{
  if (argc < 3) 
     {
      cout << "Usage: mtag RULESFILE files_extension. Read README for the details." << endl;
      return 0;
     }

  cout << "mtag: the command line tool for media files tagging" << endl;
  cout << "https://github.com/psemiletov/mtag" << endl;
          
  cout << "mtag START" << endl;
 
  string rules_file = argv[1];
  string ext = argv[2];
  ext = "." + ext;
  
  if (argc < 4)
    {
     write_tags (rules_file, ext);
     return 0;   
    }
  
  string mode = argv[3];
  if (mode == "extract")  
    {
     cout << "extract" << endl;
     extract_tags (rules_file, ext);
    }
  
  return 0;
}
