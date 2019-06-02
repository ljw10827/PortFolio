xof 0303txt 0032
template ColorRGBA {
 <35ff44e0-6c7c-11cf-8f52-0040333594a3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <d3e16e81-7835-11cf-8f52-0040333594a3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template Material {
 <3d82ab4d-62da-11cf-ab39-0020af71e433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template TextureFilename {
 <a42790e1-7810-11cf-8f52-0040333594a3>
 STRING filename;
}

template Frame {
 <3d82ab46-62da-11cf-ab39-0020af71e433>
 [...]
}

template Matrix4x4 {
 <f6f23f45-7686-11cf-8f52-0040333594a3>
 array FLOAT matrix[16];
}

template FrameTransformMatrix {
 <f6f23f41-7686-11cf-8f52-0040333594a3>
 Matrix4x4 frameMatrix;
}

template Vector {
 <3d82ab5e-62da-11cf-ab39-0020af71e433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template MeshFace {
 <3d82ab5f-62da-11cf-ab39-0020af71e433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template Mesh {
 <3d82ab44-62da-11cf-ab39-0020af71e433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

template MeshMaterialList {
 <f6f23f42-7686-11cf-8f52-0040333594a3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material <3d82ab4d-62da-11cf-ab39-0020af71e433>]
}

template VertexElement {
 <f752461c-1e23-48f6-b9f8-8350850f336f>
 DWORD Type;
 DWORD Method;
 DWORD Usage;
 DWORD UsageIndex;
}

template DeclData {
 <bf22e553-292c-4781-9fea-62bd554bdd93>
 DWORD nElements;
 array VertexElement Elements[nElements];
 DWORD nDWords;
 array DWORD data[nDWords];
}


Material Material__25 {
 1.000000;1.000000;1.000000;1.000000;;
 10.000000;
 0.000000;0.000000;0.000000;;
 0.000000;0.000000;0.000000;;

 TextureFilename {
  "BOREAN_MINERALPOOL_01.tga";
 }
}

Frame SceneRoot {
 

 FrameTransformMatrix {
  1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000;;
 }

 Frame sc2boundsphere001 {
  

  FrameTransformMatrix {
   1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,1.943469,0.000000,1.000000;;
  }
 }

 Frame borean_mineralpool_01_0 {
  

  FrameTransformMatrix {
   1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000;;
  }

  Mesh borean_mineralpool_01_0 {
   4;
   -139.468582;1.943469;139.468582;,
   139.468582;1.943469;139.468582;,
   -139.468582;1.943469;-139.468582;,
   139.468582;1.943469;-139.468582;;
   2;
   3;0,1,2;,
   3;3,2,1;;

   MeshMaterialList {
    1;
    2;
    0,
    0;
    { Material__25 }
   }

   DeclData {
    5;
    2;0;3;0;,
    2;0;6;0;,
    2;0;7;0;,
    3;0;10;0;,
    1;0;5;0;;
    60;
    3144991521,
    1065352982,
    3144991521,
    1065353099,
    997507761,
    3077178615,
    0,
    3144991633,
    3212836747,
    1065353216,
    1065353216,
    1065353216,
    1065353216,
    973078528,
    973078528,
    3144991521,
    1065352982,
    3144991521,
    1065353099,
    997507761,
    3077178615,
    0,
    3144991633,
    3212836747,
    1065353216,
    1065353216,
    1065353216,
    1065353216,
    1065336832,
    973078528,
    3144991521,
    1065352982,
    3144991521,
    1065353099,
    997507761,
    3077178615,
    0,
    3144991633,
    3212836747,
    1065353216,
    1065353216,
    1065353216,
    1065353216,
    973078528,
    1065336832,
    3144991521,
    1065352982,
    3144991521,
    1065353099,
    997507761,
    3077178615,
    0,
    3144991633,
    3212836747,
    1065353216,
    1065353216,
    1065353216,
    1065353216,
    1065336832,
    1065336832;
   }
  }
 }
}