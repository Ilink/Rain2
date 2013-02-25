#include "objParser.h"

void parseObj(string filename, vector<mesh>& meshes){
    /*
    open the file
    parse
        pack into vertex struct
        pack indexes into vector
    */
    ifstream in(filename, ios::in);
    if (!in) { 
        cerr << "Cannot open " << filename << endl;
        return;
    }

    // only supporting a single mesh for right now
    mesh newMesh;
    meshes.push_back(newMesh);

    // temporary structures
    vector<pos> positions;
    vector<tex> texs;
    vector<normal> normals;

    string line;
    int i = 0;
    int j = 0;
    int k = 0;

    bool faceCheck = true;
    bool parseFaceTripple = false;



    /*

    The data is organized for optimal opengl usage. This means all the vertex properties get packed into
    a single struct. Then we can use interleaving when we send the data to the videocard. 
    */

    while (getline(in, line)) {
        if(line.substr(0,2) == "v "){
            pos _pos;

            istringstream strm(line.substr(2)); // we want to skip the 'v ' part of the line
            if (!(strm >> _pos.x >> _pos.y >> _pos.z)) { 
                cerr << "error parsing verts" << "\n";
                return;
            }
            positions.push_back(_pos);
        } else if (line.substr(0,3) == "vn "){
            normal _normal;

            istringstream strm(line.substr(3));
            if (!(strm >> _normal.nx >> _normal.ny >> _normal.nz)) { 
                cerr << "error parsing normals" << "\n";
                return;
            }
            normals.push_back(_normal);
        } else if (line.substr(0,3) == "vt "){
            tex _tex;

            istringstream strm(line.substr(3));
            if (!(strm >> _tex.u >> _tex.v)) { 
                cerr << "error parsing normals" << "\n";
                return;
            }
            texs.push_back(_tex);
        }
    }

    in.clear();
    in.seekg(0, ios::beg);

    while (getline(in, line)) {
        if (line.substr(0,2) == "f "){
            vertex vert;

            if(faceCheck){
                unsigned int slash = line.find("/");
                if(slash != string::npos){
                    parseFaceTripple = true;
                }
                faceCheck = false;
            }

            if(parseFaceTripple){
                int index;
                string curNum;
                int start = 2;
                int end = 2;
                int length = line.length();
                int numTokens = 0;
                for(int i=2; i < length; i++){
                    // printf("line @ i: %c\n", line[i]);
                    if(line[i] == '/' || line[i] == ' '){
                        end = i;
                        curNum = line.substr(start, end-start);
                        index = strtol(curNum.c_str(), NULL, 10) - 1; // OBJ uses 1-based indexes, while opengl uses 0 based
                        start = i+1;
                        // printf("index: %i tokens: %i\n", index, numTokens);
                        if(numTokens==0){
                            vert.x = positions[index].x;
                            vert.y = positions[index].y;
                            vert.z = positions[index].z;
                            meshes[0].indexes.push_back(index);
                            numTokens++;
                        } else if (numTokens==1){
                            vert.u = texs[index].u;
                            vert.v = texs[index].v;
                            numTokens++;
                        } else if (numTokens==2){
                            vert.nx = normals[index].nx;
                            vert.ny = normals[index].ny;
                            vert.nz = normals[index].nz;
                            numTokens = 0;
                            meshes[0].verts.push_back(vert);
                        }
                    }
                }
            } else {
                istringstream strm(line.substr(2));
                GLuint a, b, c;
                if(!(strm >> a >> b >> c)){
                    cerr << "error parsing faces" << "\n";
                    return;
                }
                a--; b--; c--;
                // OBJ uses 1-based indexes, while opengl uses 0 based
                meshes[0].indexes.push_back(a);
                meshes[0].indexes.push_back(b);
                meshes[0].indexes.push_back(c);
            }
        }
    }

}