import sys
import logging


class _Feature:
    def __init__(self, default_enabled, python3_only=False, msg=None):
        self.is_python3_only = python3_only
        python_major_version = sys.version_info[0]
        self.is_enabled = default_enabled and not (
            python_major_version < 3 and python3_only
        )
        self.is_togglable = not (python_major_version < 3 and python3_only)
        self.msg = msg


class FeatureToggling:
    _conf = {
        "new-storage": _Feature(
            default_enabled=False,
            python3_only=True,
            msg="The new storage solution is experimental! "
                "In particular it starts a http server on your computer serving the "
                "data from ERT and should therefore not be used on confidential data.",
        ),
    }

    @staticmethod
    def is_enabled(feature_name):
        return FeatureToggling._conf[feature_name].is_enabled

    @staticmethod
    def add_feature_toggling_args(parser):
        for feature_name, feature in FeatureToggling._conf.items():
            if not feature.is_togglable:
                continue

            parser.add_argument(
                "--{}".format(FeatureToggling._get_arg_name(feature_name)),
                action="store_true",
                help="Toggle {} (Warning: This is experimental)".format(feature_name),
                default=False,
            )

    @staticmethod
    def update_from_args(args):
        args_dict = vars(args)
        for feature_name, feature in FeatureToggling._conf.items():
            if not feature.is_togglable:
                continue

            arg_name = FeatureToggling._get_arg_name(feature_name)
            feature_name_escaped = arg_name.replace("-", "_")

            if feature_name_escaped in args_dict and args_dict[feature_name_escaped]:
                current_state = FeatureToggling._conf[feature_name].is_enabled
                FeatureToggling._conf[feature_name].is_enabled = not current_state

            if (
                FeatureToggling._conf[feature_name].is_enabled
                and FeatureToggling._conf[feature_name].msg is not None
            ):
                logger = logging.getLogger()
                logger.warning(FeatureToggling._conf[feature_name].msg)

    @staticmethod
    def _get_arg_name(feature_name):
        default_state = FeatureToggling._conf[feature_name].is_enabled
        arg_default_state = "disable" if default_state else "enable"
        return "{}-{}".format(arg_default_state, feature_name)


def feature_enabled(feature_name):
    def decorator(func):
        def wrapper(*args, **kwargs):
            if FeatureToggling.is_enabled(feature_name):
                return func(*args, **kwargs)
            else:
                return None

        return wrapper

    return decorator
