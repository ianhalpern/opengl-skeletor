/********************************
I downloaded the models used in the program from...
http://md2.sitters-electronics.nl/
http://nehe.gamedev.net/
********************************/
#include "md2loader/Md2Model.h"

Md2Object skeletor, guy, van, motor, plant, plant2;

string modelDir = "md2_models/";

void changeModelAnimation(Md2Object *modelObj, int nAnimation) {
	const Md2Model *model = modelObj->model ();
	Md2Model::AnimMap::const_iterator itor;
	int i = 0;
	for (itor = model->anims ().begin (); itor != model->anims ().end (); ++itor) {
		if (i==nAnimation) {
			modelObj->setAnim (itor->first);
		}
		i++;
	}
}

void loadModel(Md2Object *modelObj, string model_path, string texture_path, GLfloat scale, int nAnimation) {
	Md2Model *model;
	string path = modelDir;
	path += model_path;
	model = new Md2Model(path);
	
	path = modelDir;
	path += texture_path;
	model->loadTexture (path);
	model->setTexture (path);
	
	modelObj->setModel (model);
	modelObj->setScale(scale);
	
	
	
	
	changeModelAnimation(modelObj, nAnimation);
}



void loadMD2Models() {
	loadModel(&skeletor, "skeletor/tris.md2", "skeletor/hueteotl.tga", 1.0f, 5);
	loadModel(&guy, "Sodf8/Tris.MD2", "Sodf8/Abarlith.pcx", 1.0f, 15);
	loadModel(&van, "van/tris.md2", "van/van.tga", 0.3f, 0);
	loadModel(&motor, "motor/motor.md2", "motor/motor.tga", 1.0f, 0);
	loadModel(&plant, "plant/plant.md2", "plant/plant.tga", 1.0f, 0);
	loadModel(&plant2, "plant2/plant2.md2", "plant2/plant2.tga", 1.0f, 0);
}
