struct Material {
	Material() : ka(0.7), kd(0.7), ks(0.7), specAlpha(0.3), reflect(0.4), opacity(0){}

	double ka;
	double kd;
	double ks;

	double specAlpha;
	double reflect;
	double opacity;

	bool operator==(const Material& other)
	{
		return (this->ka == other.ka) &&
			(this->kd == other.kd) &&
			(this->ks == other.ks) &&
			(this->specAlpha == other.specAlpha) &&
			(this->reflect == other.reflect) &&
			(this->opacity == other.opacity);
	}
};