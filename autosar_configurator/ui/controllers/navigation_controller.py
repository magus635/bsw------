"""Navigation controller — extracted from DaVinciMainWindow (P2-6, phase 3).

Owns the search widget toggle and the "jump to" navigation that resolves a
search result (definition or instance path) to a selection in the tree view.
Holds a back-reference to the main window (``self.win``) for shared state
(search_widget, tree_view, config_manager, module_def, current_project,
statusbar) and Qt parenting.

Note: ``_show_definition_info`` and ``_find_container_by_path`` were already
dead (no callers) when this controller was extracted; they are carried over
verbatim to keep this change purely structural.
"""
from PySide6.QtWidgets import QMessageBox


class NavigationController:
    """Search-result navigation behaviour for the main window."""

    def __init__(self, win):
        self.win = win

    def toggle_search(self, checked: bool):
        """Toggle search widget visibility."""
        win = self.win
        if checked:
            win.search_widget.show()
            win.search_widget.focus_search()

            # Build search index with current module and configuration
            if win.current_project:
                # Project mode: index all modules
                win.search_widget.build_project_index(win.current_project)
            elif win.config_manager:
                # Single module mode
                win.search_widget.build_search_index(
                    win.module_def,
                    win.config_manager.configuration,
                    clear=True
                )
        else:
            win.search_widget.hide()

    def _on_search_result_selected(self, result_type: str, path: str):
        """Handle search result selection."""
        win = self.win
        try:
            win.statusbar.showMessage(f"🔍 Navigating to: {path}", 3000)

            # Different handling based on result type
            if result_type == 'container_def':
                # For container definitions, navigate in tree
                self._navigate_to_definition(path)
            elif result_type == 'parameter_def':
                # For parameter definitions, navigate to its container definition
                container_path = '/'.join(path.split('/')[:-1]) if '/' in path else path
                self._navigate_to_definition(container_path)
            elif result_type == 'container':
                # For container instances, select in tree
                self._navigate_to_container(path)
            elif result_type in ['parameter', 'reference']:
                # For parameter/ref values, select parent container
                container_path = '/'.join(path.split('/')[:-1]) if '/' in path else path
                self._navigate_to_container(container_path)
            else:
                win.statusbar.showMessage(f"⚠️ Unhandled result type '{result_type}' for {path}", 5000)

        except Exception as e:
            import traceback
            error_msg = f"Navigation Error: {str(e)}\n{traceback.format_exc()}"
            print(error_msg)
            QMessageBox.warning(win, "Search Navigation Failed", f"An error occurred while navigating to:\n{path}\n\nError: {str(e)}")

    def _navigate_to_definition(self, path: str):
        """Navigate to a definition in tree view."""
        win = self.win
        parts = path.split('/')
        if not parts:
            return

        module_name = parts[0]
        container_path = '/'.join(parts[1:])

        # Find correct module definition
        target_module_def = None
        if win.current_project and module_name in win.current_project.module_managers:
            target_module_def = win.current_project.module_managers[module_name].module_def
        elif win.module_def and win.module_def.short_name == module_name:
            target_module_def = win.module_def

        if not target_module_def:
            win.statusbar.showMessage(f"Could not find module definition for {module_name}", 3000)
            return

        container_def = target_module_def.get_container_def(container_path)
        if container_def:
            if win.tree_view.select_definition(container_def.definition_ref):
                win.statusbar.showMessage(f"✓ Navigated to definition: {container_path}", 3000)
            else:
                win.statusbar.showMessage(f"✗ Definition found in model but failed to locate in Tree View: {container_path}", 5000)
        else:
            win.statusbar.showMessage(f"✗ Definition not found in module '{module_name}': {container_path}", 5000)

    def _show_definition_info(self, result_type: str, path: str):
        """Show definition information in a dialog. (Currently unused.)"""
        win = self.win
        parts = path.split('/')
        module_name = parts[0]

        # Find correct module definition
        target_module_def = None
        if win.current_project and module_name in win.current_project.module_managers:
            target_module_def = win.current_project.module_managers[module_name].module_def
        elif win.module_def and win.module_def.short_name == module_name:
            target_module_def = win.module_def

        if not target_module_def:
            win.statusbar.showMessage(f"Could not find module definition for {module_name}", 3000)
            return

        if result_type == 'container_def':
            # Path is Module/Path
            container_path = '/'.join(parts[1:])
            container_def = target_module_def.get_container_def(container_path)
            if container_def:
                info = f"Container: {container_def.short_name}\n"
                info += f"Description: {container_def.description or 'N/A'}\n"
                info += f"Multiplicity: {container_def.lower_multiplicity}..{container_def.upper_multiplicity}\n"
                info += f"Parameters: {len(container_def.parameters)}\n"
                info += f"Sub-containers: {len(container_def.sub_containers)}"
                QMessageBox.information(win, "Container Definition", info)
        elif result_type == 'parameter_def':
            # Path is Module/ContainerPath/Param
            container_path = '/'.join(parts[1:-1])
            param_name = parts[-1]
            container_def = target_module_def.get_container_def(container_path)
            if container_def and param_name in container_def.parameters:
                param_def = container_def.parameters[param_name]
                info = f"Parameter: {param_name}\n"
                info += f"Type: {param_def.param_type}\n"
                info += f"Description: {param_def.description or 'N/A'}\n"
                if param_def.min_value is not None:
                    info += f"Min: {param_def.min_value}\n"
                if param_def.max_value is not None:
                    info += f"Max: {param_def.max_value}\n"
                if param_def.default_value is not None:
                    info += f"Default: {param_def.default_value}"
                QMessageBox.information(win, "Parameter Definition", info)

    def _navigate_to_container(self, path: str):
        """Navigate to a container instance in tree view."""
        win = self.win
        parts = path.split('/')
        if not parts:
            return

        module_name = parts[0]

        # Find correct module manager
        target_manager = None
        if win.current_project and module_name in win.current_project.module_managers:
            target_manager = win.current_project.module_managers[module_name]
        elif win.config_manager and win.config_manager.module_def.short_name == module_name:
            target_manager = win.config_manager

        if not target_manager:
            win.statusbar.showMessage(f"Could not find module {module_name}", 3000)
            return

        # Registry lookup needs leading slash prefix: /Module/ContainerPath
        full_path = f"/{path}"
        instance = target_manager.configuration.get_instance_by_path(full_path)

        if instance:
            if win.tree_view._select_instance(instance):
                win.statusbar.showMessage(f"✓ Navigated to: {path}", 3000)
            else:
                win.statusbar.showMessage(f"✗ Instance found in model but failed to locate in Tree View: {path}", 5000)
        else:
            win.statusbar.showMessage(f"✗ Container instance not found: {path}", 5000)

    def _find_container_by_path(self, path_parts):
        """Find container instance by path. (Currently unused.)"""
        if not self.win.config_manager:
            return None

        containers = self.win.config_manager.configuration.containers
        current = None

        for part in path_parts:
            found = None
            for container in containers:
                if container.short_name == part:
                    found = container
                    current = container
                    containers = container.sub_containers
                    break
            if not found:
                return None

        return current
