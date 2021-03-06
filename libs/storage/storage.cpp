#include "pxt.h"

#if CONFIG_ENABLED(DEVICE_USB)

#include "GhostFAT.h"

class ArcadeFAT : public GhostFAT {
protected:
  static void readCfg(GFATEntry *ent, unsigned blockAddr, char *dst);

public:
  ArcadeFAT() {}
  virtual const char *volumeLabel() { return "ARCADE"; }
  virtual void addFiles();
};

void ArcadeFAT::readCfg(GFATEntry *ent, unsigned blockAddr, char *dst) {
  // auto th = (ArcadeFAT*)ent->userdata;
  memcpy(dst, (void *)(BOOTLOADER_START_ADDR + blockAddr * 512), 512);
}

void ArcadeFAT::addFiles() {
  GhostFAT::addFiles();
  addFile(readCfg, this, "config.bin",
          BOOTLOADER_END_ADDR - BOOTLOADER_START_ADDR);
}

namespace storage {

//%
void init() {
  auto msc = new ArcadeFAT();
  usb.add(*msc);
}

} // namespace storage

#endif










