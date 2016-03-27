struct Material {
	Material() : ka(Vector3(0.3f, 0.7f, 0.7f)), kd(Vector3(0.7f, 0.7f, 0.7f)), ks(Vector3(0.7f, 0.7f, 0.7f)){}

	Vector3 ka;
	Vector3 kd;
	Vector3 ks;
	float shiny;
	float reflect;

	Material(float shiny, float reflect)
	{
		this->shiny = shiny;
		this->reflect = reflect;
	}

	//double specAlpha;
	//double reflect;
	//double opacity;

	/*
	bool operator==(const Material& other)
	{
		return (this->ka == other.ka) &&
			(this->kd == other.kd) &&
			(this->ks == other.ks) &&
			(this->specAlpha == other.specAlpha) &&
			(this->reflect == other.reflect) &&
			(this->opacity == other.opacity);
	}*/
};