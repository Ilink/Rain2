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

    string line;
    int i = 0;
    int j = 0;

    bool faceCheck = true;
    bool parseFaceTripple = false;

    /*
    My parsing strategy is fairly simple.
    It assumes (currently) that vertexes occur first, but that is fairly trivial to re-work.
    The keeps track of how many secondary vertex properties we have found.
    This means it assumes every vertex has a normal and a texture coordinate.

    The data is organized for optimal opengl usage. This means all the vertex properties get packed into
    a single struct. Then we can use interleaving when we send the data to the videocard. 
    */

    while (getline(in, line)) {
        if(line.substr(0,2) == "v "){
            vertex vert;
            vert.nx = 0.0; vert.ny = 0.0; vert.nz = 0.0;
            vert.u = 0.0; vert.v = 0.0;
            istringstream strm(line.substr(2)); // we want to skip the 'v ' part of the line
            if (!(strm >> vert.x >> vert.y >> vert.z)) { 
                cerr << "error parsing verts" << "\n";
                return;
            }
            meshes[0].verts.push_back(vert);
        } else if (line.substr(0,3) == "vn "){
            if(meshes[0].verts.size() > i){
                istringstream strm(line.substr(3));
                if (!(strm >> meshes[0].verts[i].nx >> meshes[0].verts[i].ny >> meshes[0].verts[i].nz)) { 
                    cerr << "error parsing normals" << "\n";
                    return;
                }
            }

            // if i > verts.size(), push new vert onto vector
            i++;
        } else if (line.substr(0,3) == "vt "){
            if(meshes[0].verts.size() > j){
                istringstream strm(line.substr(3));
                if(!(strm >> meshes[0].verts[j].u >> meshes[0].verts[j].v)){
                    cerr << "error parsing texture coordinates" << "\n";
                    return;
                }
            }

            j++;
        } else if (line.substr(0,2) == "f "){
            if(faceCheck){
                unsigned int slash = line.find("/");
                if(slash != string::npos){
                    parseFaceTripple = true;
                }
                faceCheck = false;
            }

            if(parseFaceTripple){
                int num;
                string curNum;
                int start = 0;
                int end = 0;
                int length = line.length();
                int numTokens = 0;
                for(int i=0; i < length; i++){
                    if(line[i] == '/' || line[i] == ' '){
                        end = i;
                        curNum = line.substr(start, end-start);
                        num = strtol(curNum.c_str(), NULL, 10);
                        start = i+1;
                        if(numTokens%3 == 0){
                            //printf("num: %i\n", num);
                            meshes[0].indexes.push_back(num);
                        }
                        numTokens++;
                    }
                };
            } else {
                istringstream strm(line.substr(2));
                GLuint a, b, c;
                if(!(strm >> a >> b >> c)){
                    cerr << "error parsing faces" << "\n";
                    return;
                }
                // OBJ uses 1-based indexes, while opengl uses 0 based
                meshes[0].indexes.push_back(a-1);
                meshes[0].indexes.push_back(b-1);
                meshes[0].indexes.push_back(c-1);
            }
            
        }

        
    }

}