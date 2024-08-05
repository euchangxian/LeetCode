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
| 0002 | AddTwoNumbers | [![Rust](assets/rust.svg)](Rust/0002-AddTwoNumbers/Solution.rs) |
| 0003 | LongestSubstringWithoutRepeatingCharacters | [![C++](assets/c++.svg)](C++/0003-LongestSubstringWithoutRepeatingCharacters/Solution.cpp) |
| 0005 | LongestPalindromicSubstring | [![C++](assets/c++.svg)](C++/0005-LongestPalindromicSubstring/Solution.cpp) |
| 0011 | ContainerWithMostWater | [![C++](assets/c++.svg)](C++/0011-ContainerWithMostWater/Solution.cpp) |
| 0014 | LongestCommonPrefix | [![C++](assets/c++.svg)](C++/0014-LongestCommonPrefix/Solution.cpp) |
| 0015 | ThreeSum | [![C++](assets/c++.svg)](C++/0015-ThreeSum/Solution.cpp) |
| 0020 | ValidParentheses | [![C++](assets/c++.svg)](C++/0020-ValidParentheses/Solution.cpp) |
| 0022 | GenerateParentheses | [![C++](assets/c++.svg)](C++/0022-GenerateParentheses/Solution.cpp) [![Go](assets/go.svg)](Go/0022-GenerateParentheses/Solution.go) |
| 0032 | LongestValidParentheses | [![Rust](assets/rust.svg)](Rust/0032-LongestValidParentheses/Solution.rs) |
| 0036 | ValidSudoku | [![C++](assets/c++.svg)](C++/0036-ValidSudoku/Solution.cpp) |
| 0042 | TrappingRainWater | [![C++](assets/c++.svg)](C++/0042-TrappingRainWater/Solution.cpp) [![Go](assets/go.svg)](Go/0042-TrappingRainWater/Solution.go) |
| 0045 | JumpGame | [![Go](assets/go.svg)](Go/0045-JumpGame/Solution.go) |
| 0046 | Permutations | [![C++](assets/c++.svg)](C++/0046-Permutations/Solution.cpp) |
| 0049 | GroupAnagrams | [![C++](assets/c++.svg)](C++/0049-GroupAnagrams/Solution.cpp) |
| 0055 | JumpGame | [![Go](assets/go.svg)](Go/0055-JumpGame/Solution.go) |
| 0058 | LengthOfLastWord | [![Rust](assets/rust.svg)](Rust/0058-LengthOfLastWord/Solution.rs) |
| 0062 | UniquePaths | [![Go](assets/go.svg)](Go/0062-UniquePaths/Solution.go) |
| 0063 | UniquePathsII | [![Go](assets/go.svg)](Go/0063-UniquePathsII/Solution.go) |
| 0064 | MinimumPathSum | [![Go](assets/go.svg)](Go/0064-MinimumPathSum/Solution.go) |
| 0067 | AddBinary | [![Go](assets/go.svg)](Go/0067-AddBinary/Solution.go) |
| 0070 | ClimbingStairs | [![Go](assets/go.svg)](Go/0070-ClimbingStairs/Solution.go) |
| 0072 | EditDistance | [![Rust](assets/rust.svg)](Rust/0072-EditDistance/Solution.rs) |
| 0074 | SearchA2DMatrix | [![C++](assets/c++.svg)](C++/0074-SearchA2DMatrix/Solution.cpp) |
| 0075 | SortColors | [![C++](assets/c++.svg)](C++/0075-SortColors/Solution.cpp) |
| 0076 | MinimumWindowSubstring | [![C++](assets/c++.svg)](C++/0076-MinimumWindowSubstring/Solution.cpp) |
| 0078 | Subsets | [![C++](assets/c++.svg)](C++/0078-Subsets/Solution.cpp) |
| 0084 | LargestRectangleInHistogram | [![C++](assets/c++.svg)](C++/0084-LargestRectangleInHistogram/Solution.cpp) |
| 0094 | BinaryTreeInorderTraversal | [![Go](assets/go.svg)](Go/0094-BinaryTreeInorderTraversal/Solution.go) |
| 0097 | InterleavingString | [![Rust](assets/rust.svg)](Rust/0097-InterleavingString/Solution.rs) |
| 0098 | ValidateBinarySearchTree | [![Go](assets/go.svg)](Go/0098-ValidateBinarySearchTree/Solution.go) |
| 0118 | PascalsTriangle | [![Go](assets/go.svg)](Go/0118-PascalsTriangle/Solution.go) |
| 0120 | Triangle | [![Go](assets/go.svg)](Go/0120-Triangle/Solution.go) |
| 0121 | BestTimeToBuyAndSellStock | [![C++](assets/c++.svg)](C++/0121-BestTimeToBuyAndSellStock/Solution.cpp) [![Go](assets/go.svg)](Go/0121-BestTimeToBuyAndSellStock/Solution.go) |
| 0122 | BestTimeToBuyAndSellStockTwo | [![Go](assets/go.svg)](Go/0122-BestTimeToBuyAndSellStockTwo/Solution.go) |
| 0125 | ValidPalindrome | [![C++](assets/c++.svg)](C++/0125-ValidPalindrome/Solution.cpp) |
| 0128 | LongestConsecutiveSequence | [![C++](assets/c++.svg)](C++/0128-LongestConsecutiveSequence/Solution.cpp) |
| 0131 | PalindromePartitioning | [![C++](assets/c++.svg)](C++/0131-PalindromePartitioning/Solution.cpp) |
| 0136 | SingleNumber | [![Go](assets/go.svg)](Go/0136-SingleNumber/Solution.go) |
| 0140 | WordBreakTwo | [![C++](assets/c++.svg)](C++/0140-WordBreakTwo/Solution.cpp) |
| 0144 | BinaryTreePreorderTraversal | [![Go](assets/go.svg)](Go/0144-BinaryTreePreorderTraversal/Solution.go) |
| 0145 | BinaryTreePostorderTraversal | [![Go](assets/go.svg)](Go/0145-BinaryTreePostorderTraversal/Solution.go) |
| 0150 | EvaluateReversePolishNotation | [![C++](assets/c++.svg)](C++/0150-EvaluateReversePolishNotation/Solution.cpp) |
| 0165 | CompareVersionNumbers | [![Go](assets/go.svg)](Go/0165-CompareVersionNumbers/Solution.go) |
| 0167 | TwoSumTwo | [![C++](assets/c++.svg)](C++/0167-TwoSumTwo/Solution.cpp) |
| 0198 | HouseRobber | [![C++](assets/c++.svg)](C++/0198-HouseRobber/Solution.cpp) |
| 0199 | BinaryTreeRightSideView | [![Go](assets/go.svg)](Go/0199-BinaryTreeRightSideView/Solution.go) |
| 0213 | HouseRobberTwo | [![C++](assets/c++.svg)](C++/0213-HouseRobberTwo/Solution.cpp) |
| 0236 | LowestCommonAncestorOfABinaryTree | [![C++](assets/c++.svg)](C++/0236-LowestCommonAncestorOfABinaryTree/Solution.cpp) |
| 0237 | DeleteNodeInALinkedList | [![Go](assets/go.svg)](Go/0237-DeleteNodeInALinkedList/Solution.go) |
| 0238 | ProductOfArrayExceptSelf | [![C++](assets/c++.svg)](C++/0238-ProductOfArrayExceptSelf/Solution.cpp) |
| 0239 | SlidingWindowMaximum | [![C++](assets/c++.svg)](C++/0239-SlidingWindowMaximum/Solution.cpp) |
| 0260 | SingleNumberThree | [![C++](assets/c++.svg)](C++/0260-SingleNumberThree/Solution.cpp) |
| 0344 | ReverseString | [![C++](assets/c++.svg)](C++/0344-ReverseString/Solution.cpp) |
| 0347 | TopKFrequentElements | [![C++](assets/c++.svg)](C++/0347-TopKFrequentElements/Solution.cpp) |
| 0350 | IntersectionOfTwoArrays | [![C++](assets/c++.svg)](C++/0350-IntersectionOfTwoArrays/Solution.cpp) |
| 0402 | RemoveKDigits | [![Go](assets/go.svg)](Go/0402-RemoveKDigits/Solution.go) |
| 0404 | SumOfLeftLeaves | [![Go](assets/go.svg)](Go/0404-SumOfLeftLeaves/Solution.go) |
| 0409 | LongestPalindrome | [![C++](assets/c++.svg)](C++/0409-LongestPalindrome/Solution.cpp) |
| 0424 | LongestRepeatingCharacterReplacement | [![C++](assets/c++.svg)](C++/0424-LongestRepeatingCharacterReplacement/Solution.cpp) |
| 0452 | MinimumNumberOfArrowsToBurstBalloons | [![Go](assets/go.svg)](Go/0452-MinimumNumberOfArrowsToBurstBalloons/Solution.go) |
| 0506 | RelativeRanks | [![Go](assets/go.svg)](Go/0506-RelativeRanks/Solution.go) |
| 0523 | ContinuousSubarraySum | [![C++](assets/c++.svg)](C++/0523-ContinuousSubarraySum/Solution.cpp) |
| 0552 | StudentAttendanceRecordTwo | [![C++](assets/c++.svg)](C++/0552-StudentAttendanceRecordTwo/Solution.cpp) |
| 0567 | PermutationInString | [![C++](assets/c++.svg)](C++/0567-PermutationInString/Solution.cpp) |
| 0605 | CanPlaceFlowers | [![Go](assets/go.svg)](Go/0605-CanPlaceFlowers/Solution.go) |
| 0648 | ReplaceWords | [![C++](assets/c++.svg)](C++/0648-ReplaceWords/Solution.cpp) |
| 0704 | BinarySearch | [![C++](assets/c++.svg)](C++/0704-BinarySearch/Solution.cpp) |
| 0726 | NumberOfAtoms | [![C++](assets/c++.svg)](C++/0726-NumberOfAtoms/Solution.cpp) |
| 0739 | DailyTemperatures | [![C++](assets/c++.svg)](C++/0739-DailyTemperatures/Solution.cpp) [![Go](assets/go.svg)](Go/0739-DailyTemperatures/Solution.go) |
| 0786 | KthSmallestPrimeFraction | [![Rust](assets/rust.svg)](Rust/0786-KthSmallestPrimeFraction/Solution.rs) |
| 0846 | HandOfStraights | [![C++](assets/c++.svg)](C++/0846-HandOfStraights/Solution.cpp) |
| 0853 | CarFleet | [![C++](assets/c++.svg)](C++/0853-CarFleet/Solution.cpp) |
| 0857 | MinimumCostToHireKWorkers | [![Rust](assets/rust.svg)](Rust/0857-MinimumCostToHireKWorkers/Solution.rs) |
| 0861 | ScoreAfterFlippingMatrix | [![Rust](assets/rust.svg)](Rust/0861-ScoreAfterFlippingMatrix/Solution.rs) |
| 0881 | BoatsToSavePeople | [![Go](assets/go.svg)](Go/0881-BoatsToSavePeople/Solution.go) |
| 0912 | SortAnArray | [![C++](assets/c++.svg)](C++/0912-SortAnArray/Solution.cpp) |
| 0938 | RangeSumOfBST | [![Go](assets/go.svg)](Go/0938-RangeSumOfBST/Solution.go) |
| 0945 | MinimumIncrementToMakeArrayUnique | [![C++](assets/c++.svg)](C++/0945-MinimumIncrementToMakeArrayUnique/Solution.cpp) |
| 0979 | DistributeCoinsInBinaryTree | [![C++](assets/c++.svg)](C++/0979-DistributeCoinsInBinaryTree/Solution.cpp) |
| 1002 | FindCommonCharacters | [![C++](assets/c++.svg)](C++/1002-FindCommonCharacters/Solution.cpp) |
| 1051 | HeightChecker | [![C++](assets/c++.svg)](C++/1051-HeightChecker/Solution.cpp) |
| 1071 | GCDOfStrings | [![Go](assets/go.svg)](Go/1071-GCDOfStrings/Solution.go) |
| 1105 | FillingBookcaseShelves | [![C++](assets/c++.svg)](C++/1105-FillingBookcaseShelves/Solution.cpp) |
| 1110 | DeleteNodesAndReturnForest | [![C++](assets/c++.svg)](C++/1110-DeleteNodesAndReturnForest/Solution.cpp) |
| 1122 | RelativeSortArray | [![C++](assets/c++.svg)](C++/1122-RelativeSortArray/Solution.cpp) |
| 1143 | LongestCommonSubsequence | [![Go](assets/go.svg)](Go/1143-LongestCommonSubsequence/Solution.go) |
| 1190 | ReverseSubstringsBetweenEachPairOfParentheses | [![C++](assets/c++.svg)](C++/1190-ReverseSubstringsBetweenEachPairOfParentheses/Solution.cpp) |
| 1208 | GetEqualSubstringsWithinBudget | [![C++](assets/c++.svg)](C++/1208-GetEqualSubstringsWithinBudget/Solution.cpp) |
| 1219 | PathWithMaximumGold | [![Rust](assets/rust.svg)](Rust/1219-PathWithMaximumGold/Solution.rs) |
| 1255 | MaximumScoreWordsFormedByLetters | [![C++](assets/c++.svg)](C++/1255-MaximumScoreWordsFormedByLetters/Solution.cpp) |
| 1325 | DeleteLeavesWithAGivenValue | [![C++](assets/c++.svg)](C++/1325-DeleteLeavesWithAGivenValue/Solution.cpp) |
| 1334 | FindTheCityWithTheSmallestNumberOfNeighboursAtAThresholdDistance | [![C++](assets/c++.svg)](C++/1334-FindTheCityWithTheSmallestNumberOfNeighboursAtAThresholdDistance/Solution.cpp) |
| 1380 | LuckyNumbersInAMatrix | [![C++](assets/c++.svg)](C++/1380-LuckyNumbersInAMatrix/Solution.cpp) |
| 1395 | CountNumberOfTeams | [![C++](assets/c++.svg)](C++/1395-CountNumberOfTeams/Solution.cpp) |
| 1404 | NumberOfStepsToReduceANumberInBinaryRepresentationToOne | [![C++](assets/c++.svg)](C++/1404-NumberOfStepsToReduceANumberInBinaryRepresentationToOne/Solution.cpp) |
| 1431 | KidsWithGreatestNumberOfCandies | [![Go](assets/go.svg)](Go/1431-KidsWithGreatestNumberOfCandies/Solution.go) |
| 1442 | CountTripletsThatCanFormTwoArraysOfEqualXOR | [![C++](assets/c++.svg)](C++/1442-CountTripletsThatCanFormTwoArraysOfEqualXOR/Solution.cpp) |
| 1460 | MakeTwoArraysEqualByReversingSubarrays | [![C++](assets/c++.svg)](C++/1460-MakeTwoArraysEqualByReversingSubarrays/Solution.cpp) |
| 1509 | MinimumDifferenceBetweenLargestAndSmallestValueInThreeMoves | [![C++](assets/c++.svg)](C++/1509-MinimumDifferenceBetweenLargestAndSmallestValueInThreeMoves/Solution.cpp) |
| 1518 | WaterBottles | [![C++](assets/c++.svg)](C++/1518-WaterBottles/Solution.cpp) |
| 1530 | NumberOfGoodLeafNodesPairs | [![C++](assets/c++.svg)](C++/1530-NumberOfGoodLeafNodesPairs/Solution.cpp) |
| 1550 | ThreeConsecutiveOdds | [![C++](assets/c++.svg)](C++/1550-ThreeConsecutiveOdds/Solution.cpp) |
| 1598 | CrawlerLogFolder | [![C++](assets/c++.svg)](C++/1598-CrawlerLogFolder/Solution.cpp) |
| 1605 | FindValidMatrixGivenRowAndColumnSums | [![C++](assets/c++.svg)](C++/1605-FindValidMatrixGivenRowAndColumnSums/Solution.cpp) |
| 1608 | SpecialArrayWithXElementsGreaterThanOrEqualX | [![C++](assets/c++.svg)](C++/1608-SpecialArrayWithXElementsGreaterThanOrEqualX/Solution.cpp) |
| 1636 | SortArrayByIncreasingFrequency | [![C++](assets/c++.svg)](C++/1636-SortArrayByIncreasingFrequency/Solution.cpp) |
| 1653 | MinimumDeletionsToMakeStringsBalanced | [![C++](assets/c++.svg)](C++/1653-MinimumDeletionsToMakeStringsBalanced/Solution.cpp) |
| 1700 | NumberOfStudentsUnableToEatLunch | [![Go](assets/go.svg)](Go/1700-NumberOfStudentsUnableToEatLunch/Solution.go) |
| 1701 | AverageWaitingTime | [![C++](assets/c++.svg)](C++/1701-AverageWaitingTime/Solution.cpp) |
| 1717 | MaximumScoreFromRemovingSubstrings | [![C++](assets/c++.svg)](C++/1717-MaximumScoreFromRemovingSubstrings/Solution.cpp) |
| 1768 | MergeStringsAlternately | [![Go](assets/go.svg)](Go/1768-MergeStringsAlternately/Solution.go) |
| 1791 | FindCenterOfStarGraph | [![C++](assets/c++.svg)](C++/1791-FindCenterOfStarGraph/Solution.cpp) |
| 1823 | FindTheWinnerOfTheCircularGame | [![C++](assets/c++.svg)](C++/1823-FindTheWinnerOfTheCircularGame/Solution.cpp) |
| 1863 | SumOfAllSubsetXORTotals | [![C++](assets/c++.svg)](C++/1863-SumOfAllSubsetXORTotals/Solution.cpp) |
| 1884 | EggDropWith2EggsAndNFloors | [![Go](assets/go.svg)](Go/1884-EggDropWith2EggsAndNFloors/Solution.go) |
| 2000 | ReversePrefixOfWord | [![Go](assets/go.svg)](Go/2000-ReversePrefixOfWord/Solution.go) |
| 2037 | MinimumNumberOfMovesToSeatEveryone | [![C++](assets/c++.svg)](C++/2037-MinimumNumberOfMovesToSeatEveryone/Solution.cpp) |
| 2045 | SecondMinimumTimeToReachDestination | [![C++](assets/c++.svg)](C++/2045-SecondMinimumTimeToReachDestination/Solution.cpp) |
| 2053 | KthDistinctStringInAnArray | [![C++](assets/c++.svg)](C++/C++/2053-KthDistinctStringInAnArray/Solution.cpp) |
| 2058 | FindTheMinimumAndMaximumNumberOfNodesBetweenCriticalPoints | [![C++](assets/c++.svg)](C++/2058-FindTheMinimumAndMaximumNumberOfNodesBetweenCriticalPoints/Solution.cpp) |
| 2073 | TimeNeededToBuyTickets | [![Go](assets/go.svg)](Go/2073-TimeNeededToBuyTickets/Solution.go) |
| 2096 | StepByStepDirectionsFromABinaryTreeNodeToAnother | [![C++](assets/c++.svg)](C++/2096-StepByStepDirectionsFromABinaryTreeNodeToAnother/Solution.cpp) |
| 2134 | MinimumSwapsToGroupAllOnesTogetherTwo | [![C++](assets/c++.svg)](C++/2134-MinimumSwapsToGroupAllOnesTogetherTwo/Solution.cpp) |
| 2181 | MergeNodesInBetweenZeros | [![C++](assets/c++.svg)](C++/2181-MergeNodesInBetweenZeros/Solution.cpp) |
| 2191 | SortTheJumbledNumbers | [![C++](assets/c++.svg)](C++/2191-SortTheJumbledNumbers/Solution.cpp) |
| 2196 | CreateBinaryTreeFromDescriptions | [![C++](assets/c++.svg)](C++/2196-CreateBinaryTreeFromDescriptions/Solution.cpp) |
| 2285 | MaximumTotalImportanceOfRoads | [![C++](assets/c++.svg)](C++/2285-MaximumTotalImportanceOfRoads/Solution.cpp) |
| 2331 | EvaluateBooleanBinaryTree | [![Rust](assets/rust.svg)](Rust/2331-EvaluateBooleanBinaryTree/Solution.rs) [![C++](assets/c++.svg)](C++/2331-EvaluateBooleanBinaryTree/Solution.cpp) |
| 2373 | LargestLocalValuesInAMatrix | [![Rust](assets/rust.svg)](Rust/2373-LargestLocalValuesInAMatrix/Solution.rs) |
| 2392 | BuildAMatrixWithConditions | [![C++](assets/c++.svg)](C++/2392-BuildAMatrixWithConditions/Solution.cpp) |
| 2418 | SortThePeople | [![C++](assets/c++.svg)](C++/2418-SortThePeople/Solution.cpp) |
| 2441 | LargestPositiveIntegerThatExistsWithItsNegative | [![Go](assets/go.svg)](Go/2441-LargestPositiveIntegerThatExistsWithItsNegative/Solution.go) |
| 2486 | AppendCharactersToMakeSubsequence | [![C++](assets/c++.svg)](C++/2486-AppendCharactersToMakeSubsequence/Solution.cpp) |
| 2487 | RemoveNodesFromLinkedList | [![Go](assets/go.svg)](Go/2487-RemoveNodesFromLinkedList/Solution.go) |
| 2582 | PassThePillow | [![C++](assets/c++.svg)](C++/2582-PassThePillow/Solution.cpp) |
| 2597 | TheNumberOfBeautifulSubsets | [![C++](assets/c++.svg)](C++/2597-TheNumberOfBeautifulSubsets/Solution.cpp) |
| 2678 | NumberOfSeniorCitizens | [![C++](assets/c++.svg)](C++/2678-NumberOfSeniorCitizens/Solution.cpp) |
| 2751 | RobotCollisions | [![C++](assets/c++.svg)](C++/2751-RobotCollisions/Solution.cpp) |
| 2812 | FindTheSafestPathInAGrid | [![Rust](assets/rust.svg)](Rust/2812-FindTheSafestPathInAGrid/Solution.rs) |
| 2816 | DoubleANumberRepresentedAsALinkedList | [![Go](assets/go.svg)](Go/2816-DoubleANumberRepresentedAsALinkedList/Solution.go) |
| 2830 | MaximizeTheProfitAsASalesman | [![Go](assets/go.svg)](Go/2830-MaximizeTheProfitAsASalesman/Solution.go) |
| 2976 | MinimumCostToConvertStringOne | [![C++](assets/c++.svg)](C++/2976-MinimumCostToConvertStringOne/Solution.cpp) |
| 3068 | FindTheMaximumSumOfNodeValues | [![C++](assets/c++.svg)](C++/3068-FindTheMaximumSumOfNodeValues/Solution.cpp) |
| 3075 | MaximizeHappinessOfSelectedChildren | [![Rust](assets/rust.svg)](Rust/3075-MaximizeHappinessOfSelectedChildren/Solution.rs) [![Go](assets/go.svg)](Go/3075-MaximizeHappinessOfSelectedChildren/Solution.go) |
| 3110 | ScoreOfAString | [![C++](assets/c++.svg)](C++/3110-ScoreOfAString/Solution.cpp) |
