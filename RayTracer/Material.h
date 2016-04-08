struct Material {

	Vector3 ka;
	Vector3 kd;
	Vector3 ks;
	float shiny;
	float reflect;

	Material()
	{
		this->ka = Vector3(0.3f, 0.3f, 0.3f);
		this->kd = Vector3(0.5f, 0.5f, 0.5f);
		this->ks = Vector3(0.8f, 0.8f, 0.8f);
		this->shiny = 0.1f;
		this->reflect = 0.0f;
	}

	Material(Vector3 ka, Vector3 kd, Vector3 ks)
	{
		this->ka = ka;
		this->kd = kd;
		this->ks = ks;
		this->shiny = 0.1f;
		this->reflect = 0.0f;
	}

	Material(float shiny, float reflect)
	{
		this->ka = Vector3(0.3f, 0.3f, 0.3f);
		this->kd = Vector3(0.5f, 0.5f, 0.5f);
		this->ks = Vector3(0.8f, 0.8f, 0.8f);
		this->shiny = shiny;
		this->reflect = reflect;
	}
};