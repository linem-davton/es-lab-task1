import subprocess
import pytest
from pathlib import Path

GTEST_EXECUTABLE = Path(__file__).parent.parent / "build" / "tests" / "test_controller"


def run_gtest(test_name):
    result = subprocess.run([GTEST_EXECUTABLE, f"--gtest_filter={test_name}"],
                            capture_output=True, text=True)
    passed = "[  PASSED  ] 1 test." in result.stdout
    return passed, result.stdout, result.stderr


@pytest.mark.parametrize("test_case", [
    "ControllerTest.BasicTest",
    "ControllerTest.IntegralTest",
    "ControllerTest.ProportionalTest",
    "ControllerTest.ProportionalTest2",
    "ControllerTest.DerivativeTest",
    "ControllerTest.ResetTest",
])
def test_gtest_wrapper(test_case):
    passed, stdout, stderr = run_gtest(test_case)
    assert passed, f"GTest '{test_case}' failed:\n{stdout}\n{stderr}"
