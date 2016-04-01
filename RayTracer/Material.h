struct Material {
	Material() : ka(Vector3(0.3f, 0.7f, 0.7f)), kd(Vector3(0.7f, 0.7f, 0.7f)), ks(Vector3(0.7f, 0.7f, 0.7f)){}

	Vector3 ka;
	Vector3 kd;
	Vector3 ks;
	float shiny;
	float reflect;

	Material(Vector3 ka, Vector3 kd, Vector3 ks)
	{
		this->ka = ka;
		this->kd = kd;
		this->ks = ks;
	}

	Material(float shiny, float reflect)
	{
		this->shiny = shiny;
		this->reflect = reflect;
	}
};