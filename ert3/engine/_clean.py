from typing import Set
from pathlib import Path

import ert3


def clean(workspace: Path, experiment_names: Set[str], clean_all: bool) -> None:
    assert not (experiment_names and clean_all)

    stored_experiments = ert3.storage.get_experiment_names(workspace=workspace)

    if clean_all:
        experiment_names = stored_experiments
    else:
        experiment_names = {
            name for name in experiment_names if name in stored_experiments
        }

    for name in experiment_names:
        ert3.storage.delete_experiment(workspace=workspace, experiment_name=name)
        ert3.evaluator.cleanup(workspace, name)
