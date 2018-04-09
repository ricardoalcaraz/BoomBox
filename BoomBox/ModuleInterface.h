class ModuleInterface {
	public:
		ModuleInterface(){}
		virtual ~ModuleInterface(){}
		virtual bool isGameCompleted()=0;
		virtual uint8_t numberErrors()=0;
		virtual void init()=0;
		virtual void update()=0;
		virtual void terminate()=0;
};
