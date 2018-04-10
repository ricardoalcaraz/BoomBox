class ModuleInterface {
	public:
		ModuleInterface(uint8_t code, Timer timer){}
		virtual ~ModuleInterface(){}
		virtual bool isGameCompleted()=0;
		virtual uint8_t numberErrors()=0;
		virtual void init()=0;
		virtual void updateModule()=0;
		virtual void terminate()=0;
};
