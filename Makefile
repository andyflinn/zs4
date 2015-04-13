.PHONY: clean All

All:
	@echo "----------Building project:[ zs4dyad - Debug ]----------"
	@cd "zs4dyad" && $(MAKE) -f  "zs4dyad.mk"
clean:
	@echo "----------Cleaning project:[ zs4dyad - Debug ]----------"
	@cd "zs4dyad" && $(MAKE) -f  "zs4dyad.mk" clean
