import { teamMembers, features, budgetData } from './data.js';
import { createTeamCard } from './modules/team-card.js';

document.addEventListener('DOMContentLoaded', () => {
    initializeMobileMenu();
    populateFeatures();
    populateTeamMembers();
    populateBudgetTable();
});

function initializeMobileMenu() {
    const menuButton = document.querySelector('.menu-button');
    const mobileMenu = document.querySelector('.mobile-menu');
    
    menuButton?.addEventListener('click', () => {
        mobileMenu?.classList.toggle('active');
    });

    document.addEventListener('click', (e) => {
        if (!mobileMenu?.contains(e.target) && !menuButton?.contains(e.target)) {
            mobileMenu?.classList.remove('active');
        }
    });
}

function populateFeatures() {
    const featuresList = document.querySelector('.features-grid');
    if (!featuresList) return;
    
    features.forEach(feature => {
        const li = document.createElement('li');
        li.textContent = feature;
        featuresList.appendChild(li);
    });
}

function populateTeamMembers() {
    const teamGrid = document.querySelector('.team-grid');
    if (!teamGrid) return;
    
    teamMembers.forEach((member, index) => {
        const card = createTeamCard(member, index);
        teamGrid.appendChild(card);
    });
}

function populateBudgetTable() {
    const tableBody = document.querySelector('tbody');
    const totalBudgetElement = document.getElementById('total-budget');
    
    if (!tableBody || !totalBudgetElement) return;
    
    let total = 0;
    
    budgetData.forEach(([category, budget]) => {
        total += budget;
        const row = document.createElement('tr');
        row.innerHTML = `
            <td>${category}</td>
            <td>${budget}</td>
        `;
        tableBody.appendChild(row);
    });

    totalBudgetElement.textContent = total;
}