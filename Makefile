.PHONY: clean All

All:
	@echo "----------Building project:[ zs4static - Debug ]----------"
	@cd "zs4static" && $(MAKE) -f  "zs4static.mk"
clean:
	@echo "----------Cleaning project:[ zs4static - Debug ]----------"
	@cd "zs4static" && $(MAKE) -f  "zs4static.mk" clean
