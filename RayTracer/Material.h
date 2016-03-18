struct Material {
	Material() : ka(Vector3(0.3, 0.7, 0.7)), kd(Vector3(0.7, 0.7, 0.7)), ks(Vector3(0.7, 0.7, 0.7)){}

	Vector3 ka;
	Vector3 kd;
	Vector3 ks;

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