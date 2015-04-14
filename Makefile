.PHONY: clean All

All:
	@echo "----------Building project:[ zs4 - Debug ]----------"
	@cd "zs4" && $(MAKE) -f  "zs4.mk"
clean:
	@echo "----------Cleaning project:[ zs4 - Debug ]----------"
	@cd "zs4" && $(MAKE) -f  "zs4.mk" clean
