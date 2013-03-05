#include "objParser.h"

void parseFN(const string& line, vector<vertex>& verts, vector<GLuint>& indexes, 
vector<normal>& normals, vector<pos>& positions, vector<tex>& texs){
    int start = 2;
    int end = 2;
    int numTokens = 0;
    vertex vert;
    int index;
    int length = line.length();
    vert.u = 0.0; vert.v = 0.0; // no texture coordinates for this
    bool skip = true;
    string curNum;

    for(int i=2; i < length; i++){
        if(line[i] == '/' || line[i] == ' '){
            if(line[i] == '/' && line[i+1] == '/'){
                i++; // skip the next character
            }
            end = i;
            string curNum = line.substr(start, end-start);
            index = strtol(curNum.c_str(), NULL, 10) - 1; // OBJ uses 1-based indexes, while opengl uses 0 based
            start = i+1;
            // printf("index: %i tokens: %i\n", index, numTokens);
            if(numTokens==0){
                vert.x = positions[index].x;
                vert.y = positions[index].y;
                vert.z = positions[index].z;
                int newIndex = verts.size();
                // indexes.push_back(index);
                indexes.push_back(newIndex);
                numTokens++;
            } else if (numTokens==1){
                vert.nx = normals[index].nx;
                vert.ny = normals[index].ny;
                vert.nz = normals[index].nz;
                numTokens = 0;
                verts.push_back(vert);
            }
        }
    }
}

void parseFTN(const string& line, vector<vertex>& verts, vector<GLuint>& indexes, 
vector<normal>& normals, vector<pos>& positions, vector<tex>& texs){
    int start = 2;
    int end = 2;
    int numTokens = 0;
    vertex vert;
    int length = line.length();
    int index;

    for(int i=2; i < length; i++){
        // printf("line @ i: %c\n", line[i]);
        if(line[i] == '/' || line[i] == ' '){
            
            end = i;
            string curNum = line.substr(start, end-start);
            index = strtol(curNum.c_str(), NULL, 10) - 1; // OBJ uses 1-based indexes, while opengl uses 0 based
            start = i+1;
            // printf("index: %i tokens: %i\n", index, numTokens);
            if(numTokens==0){
                vert.x = positions[index].x;
                vert.y = positions[index].y;
                vert.z = positions[index].z;
                int newIndex = verts.size();
                // indexes.push_back(index);
                indexes.push_back(newIndex);
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
                verts.push_back(vert);
            }
        }
    }
}

void parseFT(const string& line, vector<vertex>& verts, vector<GLuint>& indexes, 
vector<normal>& normals, vector<pos>& positions, vector<tex>& texs){
    int start = 2;
    int end = 2;
    int numTokens = 0;
    vertex vert;
    int index;
    int length = line.length();
    vert.nx = 0.0;  vert.ny = 0.0;  vert.nz = 0.0;

    for(int i=2; i < length; i++){
        // printf("line @ i: %c\n", line[i]);
        if(line[i] == '/' || line[i] == ' '){
            
            end = i;
            string curNum = line.substr(start, end-start);
            index = strtol(curNum.c_str(), NULL, 10) - 1; // OBJ uses 1-based indexes, while opengl uses 0 based
            start = i+1;
            // printf("index: %i tokens: %i\n", index, numTokens);
            if(numTokens==0){
                vert.x = positions[index].x;
                vert.y = positions[index].y;
                vert.z = positions[index].z;
                int newIndex = verts.size();
                // indexes.push_back(index);
                indexes.push_back(newIndex);
                numTokens++;
            } else if (numTokens==1){
                vert.u = texs[index].u;
                vert.v = texs[index].v;
                numTokens = 0;
                verts.push_back(vert);
            }
        }
    }
}

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
                
                int numSpaces = count(line.begin()+2, line.end(), ' ');
                unsigned doubleSlashes = line.find("//");
                unsigned int mode;
                string temp;
                /*
                There are three ways of specifying faces:
                    1. face index / tex index / normal index
                    2. face index // normal index
                    3. face index / tex index

                The way im doing this is a little brittle because it only works with triangles.
                6 slashes is 2 per pair, with 3 pairs
                */

                /*
                i need to know two things:
                    1: is it a quad or a triangle?
                    2: which type of vertex is it? (position/normal/texture etc) 
                */
                string firstSet = line.substr(2, line.find(" ", 2)-2);
                int numSlashes = count(firstSet.begin(), firstSet.end(), '/');
                if(numSpaces == 3){ // triangle
                    vector<GLuint>& indexes = meshes[0].indexes;
                } else if(numSpaces == 4){ // quad
                    vector<GLuint>& indexes = meshes[0].quadIndexes;
                }

                if(numSlashes == 2){
                    if(doubleSlashes != string::npos){
                        mode = FN; // only this mode has 2 slashes like that
                        parseFN(line, meshes[0].verts, meshes[0].indexes, normals, positions, texs);
                    } else {
                        mode = FTN;
                        // const string& line, vector<vertex>& verts, vector<GLuint>& indexes, 
                        // vector<GLfloat>& normals, vector<GLfloat>& positions, vector<GLfloat>& texs
                        parseFTN(line, meshes[0].verts, meshes[0].indexes, normals, positions, texs);
                    }
                } else if(numSlashes == 1) {
                    mode = FT;
                    parseFT(line, meshes[0].verts, meshes[0].indexes, normals, positions, texs);
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