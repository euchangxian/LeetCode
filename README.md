# LeetCode Solutions

[![pipeline status](https://gitlab.com/euchangxian/leetcode/badges/main/pipeline.svg)](https://gitlab.com/euchangxian/leetcode/-/commits/main)
[![coverage report](https://gitlab.com/euchangxian/leetcode/badges/main/coverage.svg)](https://gitlab.com/euchangxian/leetcode/-/commits/main)

[[_TOC_]]

___

## Initial Setup

To ensure that the README table is automatically updated with new Solutions,
follow these steps to set up a pre-commit hook:

```bash
git clone https://gitlab.com/euchangxian/leetcode.git
cd leetcode
bash setup_hook.sh
```

## Description

Contains LeetCode Solutions written in different languages for ME to reference.

Started with Go, but Go as an interview language to solve LeetCode questions is
a poor choice, since Go's standard library is sorely lacking.
Also, solving string/char questions in Go was painful due to runes and such.
Though Go is still my favorite language by far for Software Engineering.

Tried Rust for the fun of it. Enjoyed it. Too difficult.

Now solving in C++. Like it.

| Code | Problem Name | Languages |
| :--: | :----------- | :-------: |
| 0002 | AddTwoNumbers | ![Rust](assets/rust.svg) |
| 0003 | LongestSubstringWithoutRepeatingCharacters | ![C++](assets/c++.svg) |
| 0005 | LongestPalindromicSubstring | ![C++](assets/c++.svg) |
| 0011 | ContainerWithMostWater | ![C++](assets/c++.svg) |
| 0014 | LongestCommonPrefix | ![C++](assets/c++.svg) |
| 0015 | ThreeSum | ![C++](assets/c++.svg) |
| 0020 | ValidParentheses | ![C++](assets/c++.svg) |
| 0022 | GenerateParentheses | ![C++](assets/c++.svg) ![Go](assets/go.svg) |
| 0032 | LongestValidParentheses | ![Rust](assets/rust.svg) |
| 0036 | ValidSudoku | ![C++](assets/c++.svg) |
| 0042 | TrappingRainWater | ![C++](assets/c++.svg) ![Go](assets/go.svg) |
| 0045 | JumpGame | ![Go](assets/go.svg) |
| 0046 | Permutations | ![C++](assets/c++.svg) |
| 0049 | GroupAnagrams | ![C++](assets/c++.svg) |
| 0055 | JumpGame | ![Go](assets/go.svg) |
| 0058 | LengthOfLastWord | ![Rust](assets/rust.svg) |
| 0062 | UniquePaths | ![Go](assets/go.svg) |
| 0063 | UniquePathsII | ![Go](assets/go.svg) |
| 0064 | MinimumPathSum | ![Go](assets/go.svg) |
| 0067 | AddBinary | ![Go](assets/go.svg) |
| 0070 | ClimbingStairs | ![Go](assets/go.svg) |
| 0072 | EditDistance | ![Rust](assets/rust.svg) |
| 0074 | SearchA2DMatrix | ![C++](assets/c++.svg) |
| 0075 | SortColors | ![C++](assets/c++.svg) |
| 0076 | MinimumWindowSubstring | ![C++](assets/c++.svg) |
| 0078 | Subsets | ![C++](assets/c++.svg) |
| 0084 | LargestRectangleInHistogram | ![C++](assets/c++.svg) |
| 0094 | BinaryTreeInorderTraversal | ![Go](assets/go.svg) |
| 0097 | InterleavingString | ![Rust](assets/rust.svg) |
| 0098 | ValidateBinarySearchTree | ![Go](assets/go.svg) |
| 0118 | PascalsTriangle | ![Go](assets/go.svg) |
| 0120 | Triangle | ![Go](assets/go.svg) |
| 0121 | BestTimeToBuyAndSellStock | ![C++](assets/c++.svg) ![Go](assets/go.svg) |
| 0122 | BestTimeToBuyAndSellStockTwo | ![Go](assets/go.svg) |
| 0125 | ValidPalindrome | ![C++](assets/c++.svg) |
| 0128 | LongestConsecutiveSequence | ![C++](assets/c++.svg) |
| 0131 | PalindromePartitioning | ![C++](assets/c++.svg) |
| 0136 | SingleNumber | ![Go](assets/go.svg) |
| 0140 | WordBreakTwo | ![C++](assets/c++.svg) |
| 0144 | BinaryTreePreorderTraversal | ![Go](assets/go.svg) |
| 0145 | BinaryTreePostorderTraversal | ![Go](assets/go.svg) |
| 0150 | EvaluateReversePolishNotation | ![C++](assets/c++.svg) |
| 0165 | CompareVersionNumbers | ![Go](assets/go.svg) |
| 0167 | TwoSumTwo | ![C++](assets/c++.svg) |
| 0198 | HouseRobber | ![C++](assets/c++.svg) |
| 0199 | BinaryTreeRightSideView | ![Go](assets/go.svg) |
| 0213 | HouseRobberTwo | ![C++](assets/c++.svg) |
| 0236 | LowestCommonAncestorOfABinaryTree | ![C++](assets/c++.svg) |
| 0237 | DeleteNodeInALinkedList | ![Go](assets/go.svg) |
| 0238 | ProductOfArrayExceptSelf | ![C++](assets/c++.svg) |
| 0239 | SlidingWindowMaximum | ![C++](assets/c++.svg) |
| 0260 | SingleNumberThree | ![C++](assets/c++.svg) |
| 0344 | ReverseString | ![C++](assets/c++.svg) |
| 0347 | TopKFrequentElements | ![C++](assets/c++.svg) |
| 0350 | IntersectionOfTwoArrays | ![C++](assets/c++.svg) |
| 0402 | RemoveKDigits | ![Go](assets/go.svg) |
| 0404 | SumOfLeftLeaves | ![Go](assets/go.svg) |
| 0409 | LongestPalindrome | ![C++](assets/c++.svg) |
| 0424 | LongestRepeatingCharacterReplacement | ![C++](assets/c++.svg) |
| 0452 | MinimumNumberOfArrowsToBurstBalloons | ![Go](assets/go.svg) |
| 0506 | RelativeRanks | ![Go](assets/go.svg) |
| 0523 | ContinuousSubarraySum | ![C++](assets/c++.svg) |
| 0552 | StudentAttendanceRecordTwo | ![C++](assets/c++.svg) |
| 0567 | PermutationInString | ![C++](assets/c++.svg) |
| 0605 | CanPlaceFlowers | ![Go](assets/go.svg) |
| 0648 | ReplaceWords | ![C++](assets/c++.svg) |
| 0704 | BinarySearch | ![C++](assets/c++.svg) |
| 0726 | NumberOfAtoms | ![C++](assets/c++.svg) |
| 0739 | DailyTemperatures | ![C++](assets/c++.svg) ![Go](assets/go.svg) |
| 0786 | KthSmallestPrimeFraction | ![Rust](assets/rust.svg) |
| 0846 | HandOfStraights | ![C++](assets/c++.svg) |
| 0853 | CarFleet | ![C++](assets/c++.svg) |
| 0857 | MinimumCostToHireKWorkers | ![Rust](assets/rust.svg) |
| 0861 | ScoreAfterFlippingMatrix | ![Rust](assets/rust.svg) |
| 0881 | BoatsToSavePeople | ![Go](assets/go.svg) |
| 0912 | SortAnArray | ![C++](assets/c++.svg) |
| 0938 | RangeSumOfBST | ![Go](assets/go.svg) |
| 0945 | MinimumIncrementToMakeArrayUnique | ![C++](assets/c++.svg) |
| 0979 | DistributeCoinsInBinaryTree | ![C++](assets/c++.svg) |
| 1002 | FindCommonCharacters | ![C++](assets/c++.svg) |
| 1051 | HeightChecker | ![C++](assets/c++.svg) |
| 1071 | GCDOfStrings | ![Go](assets/go.svg) |
| 1105 | FillingBookcaseShelves | ![C++](assets/c++.svg) |
| 1110 | DeleteNodesAndReturnForest | ![C++](assets/c++.svg) |
| 1122 | RelativeSortArray | ![C++](assets/c++.svg) |
| 1143 | LongestCommonSubsequence | ![Go](assets/go.svg) |
| 1190 | ReverseSubstringsBetweenEachPairOfParentheses | ![C++](assets/c++.svg) |
| 1208 | GetEqualSubstringsWithinBudget | ![C++](assets/c++.svg) |
| 1219 | PathWithMaximumGold | ![Rust](assets/rust.svg) |
| 1255 | MaximumScoreWordsFormedByLetters | ![C++](assets/c++.svg) |
| 1325 | DeleteLeavesWithAGivenValue | ![C++](assets/c++.svg) |
| 1334 | FindTheCityWithTheSmallestNumberOfNeighboursAtAThresholdDistance | ![C++](assets/c++.svg) |
| 1380 | LuckyNumbersInAMatrix | ![C++](assets/c++.svg) |
| 1395 | CountNumberOfTeams | ![C++](assets/c++.svg) |
| 1404 | NumberOfStepsToReduceANumberInBinaryRepresentationToOne | ![C++](assets/c++.svg) |
| 1431 | KidsWithGreatestNumberOfCandies | ![Go](assets/go.svg) |
| 1442 | CountTripletsThatCanFormTwoArraysOfEqualXOR | ![C++](assets/c++.svg) |
| 1460 | MakeTwoArraysEqualByReversingSubarrays | ![C++](assets/c++.svg) |
| 1509 | MinimumDifferenceBetweenLargestAndSmallestValueInThreeMoves | ![C++](assets/c++.svg) |
| 1518 | WaterBottles | ![C++](assets/c++.svg) |
| 1530 | NumberOfGoodLeafNodesPairs | ![C++](assets/c++.svg) |
| 1550 | ThreeConsecutiveOdds | ![C++](assets/c++.svg) |
| 1598 | CrawlerLogFolder | ![C++](assets/c++.svg) |
| 1605 | FindValidMatrixGivenRowAndColumnSums | ![C++](assets/c++.svg) |
| 1608 | SpecialArrayWithXElementsGreaterThanOrEqualX | ![C++](assets/c++.svg) |
| 1636 | SortArrayByIncreasingFrequency | ![C++](assets/c++.svg) |
| 1653 | MinimumDeletionsToMakeStringsBalanced | ![C++](assets/c++.svg) |
| 1700 | NumberOfStudentsUnableToEatLunch | ![Go](assets/go.svg) |
| 1701 | AverageWaitingTime | ![C++](assets/c++.svg) |
| 1717 | MaximumScoreFromRemovingSubstrings | ![C++](assets/c++.svg) |
| 1768 | MergeStringsAlternately | ![Go](assets/go.svg) |
| 1791 | FindCenterOfStarGraph | ![C++](assets/c++.svg) |
| 1823 | FindTheWinnerOfTheCircularGame | ![C++](assets/c++.svg) |
| 1863 | SumOfAllSubsetXORTotals | ![C++](assets/c++.svg) |
| 1884 | EggDropWith2EggsAndNFloors | ![Go](assets/go.svg) |
| 2000 | ReversePrefixOfWord | ![Go](assets/go.svg) |
| 2037 | MinimumNumberOfMovesToSeatEveryone | ![C++](assets/c++.svg) |
| 2045 | SecondMinimumTimeToReachDestination | ![C++](assets/c++.svg) |
| 2058 | FindTheMinimumAndMaximumNumberOfNodesBetweenCriticalPoints | ![C++](assets/c++.svg) |
| 2073 | TimeNeededToBuyTickets | ![Go](assets/go.svg) |
| 2096 | StepByStepDirectionsFromABinaryTreeNodeToAnother | ![C++](assets/c++.svg) |
| 2134 | MinimumSwapsToGroupAllOnesTogetherTwo | ![C++](assets/c++.svg) |
| 2181 | MergeNodesInBetweenZeros | ![C++](assets/c++.svg) |
| 2191 | SortTheJumbledNumbers | ![C++](assets/c++.svg) |
| 2196 | CreateBinaryTreeFromDescriptions | ![C++](assets/c++.svg) |
| 2285 | MaximumTotalImportanceOfRoads | ![C++](assets/c++.svg) |
| 2331 | EvaluateBooleanBinaryTree | ![Rust](assets/rust.svg) ![C++](assets/c++.svg) |
| 2373 | LargestLocalValuesInAMatrix | ![Rust](assets/rust.svg) |
| 2392 | BuildAMatrixWithConditions | ![C++](assets/c++.svg) |
| 2418 | SortThePeople | ![C++](assets/c++.svg) |
| 2441 | LargestPositiveIntegerThatExistsWithItsNegative | ![Go](assets/go.svg) |
| 2486 | AppendCharactersToMakeSubsequence | ![C++](assets/c++.svg) |
| 2487 | RemoveNodesFromLinkedList | ![Go](assets/go.svg) |
| 2582 | PassThePillow | ![C++](assets/c++.svg) |
| 2597 | TheNumberOfBeautifulSubsets | ![C++](assets/c++.svg) |
| 2678 | NumberOfSeniorCitizens | ![C++](assets/c++.svg) |
| 2751 | RobotCollisions | ![C++](assets/c++.svg) |
| 2812 | FindTheSafestPathInAGrid | ![Rust](assets/rust.svg) |
| 2816 | DoubleANumberRepresentedAsALinkedList | ![Go](assets/go.svg) |
| 2830 | MaximizeTheProfitAsASalesman | ![Go](assets/go.svg) |
| 2976 | MinimumCostToConvertStringOne | ![C++](assets/c++.svg) |
| 3068 | FindTheMaximumSumOfNodeValues | ![C++](assets/c++.svg) |
| 3075 | MaximizeHappinessOfSelectedChildren | ![Rust](assets/rust.svg) ![Go](assets/go.svg) |
| 3110 | ScoreOfAString | ![C++](assets/c++.svg) |
