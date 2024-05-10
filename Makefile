PROJECT = 909_noise

GERBER_DIR = fab
BOM_DIR = bom
REPORT_DIR = reports
PDF_DIR = sch

GERBER_ZIP_FILE = $(GERBER_DIR)/$(PROJECT).zip
BOM_FILE = $(BOM_DIR)/$(PROJECT)_bom.csv
ERC_FILE = $(REPORT_DIR)/$(PROJECT)_erc.rpt
DRC_FILE = $(REPORT_DIR)/$(PROJECT)_drc.rpt
PDF_FILE = $(PDF_DIR)/$(PROJECT).pdf

CLI = kicad-cli

PRO_FILE = $(PROJECT).kicad_pro
SCH_FILE = $(PROJECT).kicad_sch
PCB_FILE = $(PROJECT).kicad_pcb


all: gerbers bom pdf erc drc

gerbers:
	mkdir -p $(GERBER_DIR)
	$(CLI) pcb export gerbers --board-plot-params --output $(GERBER_DIR)/ $(PCB_FILE)
	$(CLI) pcb export drill --output $(GERBER_DIR)/ $(PCB_FILE)
	rm -f $(GERBER_ZIP_FILE)
	zip --junk-paths $(GERBER_ZIP_FILE) fab/*

bom:
	mkdir -p $(BOM_DIR)
	$(CLI) sch export bom --preset "Grouped By Value and Footprint" --format-preset "CSV" --output $(BOM_FILE) $(SCH_FILE)

erc:
	mkdir -p $(REPORT_DIR)
	$(CLI) sch erc --format report --severity-all --output $(ERC_FILE) $(SCH_FILE)

drc:
	mkdir -p $(REPORT_DIR)
	$(CLI) pcb drc --format report --all-track-errors --schematic-parity --severity-all --output $(DRC_FILE) $(PCB_FILE)

pdf:
	mkdir -p $(PDF_DIR)
	$(CLI) sch export pdf --output $(PDF_FILE) $(SCH_FILE)

clean:
	rm -rf $(GERBER_DIR) $(BOM_DIR) $(REPORT_DIR) $(PDF_DIR)

.PHONY: gerbers bom erc drc pdf clean
