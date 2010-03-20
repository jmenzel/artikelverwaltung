.PHONY: clean All

All:
	@echo ----------Building project:[ Anwendung - Release ]----------
	@cd "Anwendung" && "$(MAKE)" -f "Anwendung.mk"
clean:
	@echo ----------Cleaning project:[ Anwendung - Release ]----------
	@cd "Anwendung" && "$(MAKE)" -f "Anwendung.mk" clean
